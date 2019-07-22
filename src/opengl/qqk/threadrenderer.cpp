//
// Created by Guarin on 2019-05-15.
//


#include "src/opengl/qqk/threadrenderer.h"
#include "heatmapscene.h"
#include "ecs/system/render.h"

#include <QtCore/QMutex>
#include <QtCore/QThread>

#include <QtGui/QOpenGLContext>
#include <QtGui/QOpenGLFramebufferObject>
#include <QtGui/QGuiApplication>
#include <QtGui/QOffscreenSurface>

#include <QtQuick/QQuickWindow>
#include <qsgsimpletexturenode.h>


QList<QThread *> HDC::SceneRenderer::threads;

/*
 * The render thread shares a context with the scene graph and will
 * render into two separate FBOs, one to use for display and one
 * to use for rendering
 */
namespace HDC{

    
    class SceneRenderThread : public QThread
    {
        Q_OBJECT
    public:
        SceneRenderThread(const QSize &size)
        : surface(nullptr)
        , context(nullptr)
        , m_renderFbo(nullptr)
        , m_displayFbo(nullptr)
        , m_renderer(nullptr)
        , m_size(size)
        {
            HDC::SceneRenderer::threads << this;
        }

        QOffscreenSurface *surface;
        QOpenGLContext *context;

        public slots:
        void renderNext()
        {
            context->makeCurrent(surface);

            if (!m_renderFbo) {
            // Initialize the buffers and renderer
                QOpenGLFramebufferObjectFormat format;
                format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
                m_renderFbo = new QOpenGLFramebufferObject(m_size, format);
                m_displayFbo = new QOpenGLFramebufferObject(m_size, format);
                m_renderer = new HDC::HeatmapRenderer();
                m_renderer->initialize();


            }

            m_renderFbo->bind();
            context->functions()->glViewport(0, 0, m_size.width(), m_size.height());

            m_renderer->render();

        // We need to flush the contents to the FBO before posting
        // the texture to the other thread, otherwise, we might
        // get unexpected results.
            context->functions()->glFlush();

            m_renderFbo->bindDefault();
            qSwap(m_renderFbo, m_displayFbo);

            emit textureReady(m_displayFbo->texture(), m_size);
        }

        void shutDown()
        {
            context->makeCurrent(surface);
            delete m_renderFbo;
            delete m_displayFbo;
            delete m_renderer;
            context->doneCurrent();
            delete context;

        // schedule this to be deleted only after we're done cleaning up
            surface->deleteLater();

        // Stop event processing, move the thread to GUI and make sure it is deleted.
            exit();
            moveToThread(QGuiApplication::instance()->thread());
        }

        ECS_SYSTEM::Renderer* getHeatmapRenderer() {
            return m_renderer;
        }

        signals:
        void textureReady(int id, const QSize &size);
        void keyPressed();


    private:
        QOpenGLFramebufferObject *m_renderFbo;
        QOpenGLFramebufferObject *m_displayFbo;

        ECS_SYSTEM::Renderer* m_renderer;
        QSize m_size;
    };

    class TextureNode : public QObject, public QSGSimpleTextureNode
    {
        Q_OBJECT

    public:
        TextureNode(QQuickWindow *window)
        : m_id(0)
        , m_size(0, 0)
        , m_texture(nullptr)
        , m_window(window)
        {
        // Our texture node must have a texture, so use the default 0 texture.
            m_texture = m_window->createTextureFromId(0, QSize(1, 1));
            setTexture(m_texture);
            setFiltering(QSGTexture::Linear);
        }

        ~TextureNode() override
        {
            delete m_texture;
        }

        signals:
        void textureInUse();
        void pendingNewTexture();

        public slots:

    // This function gets called on the FBO rendering thread and will store the
    // texture id and size and schedule an update on the window.
        void newTexture(int id, const QSize &size) {
            m_mutex.lock();
            m_id = id;
            m_size = size;
            m_mutex.unlock();

        // We cannot call QQuickWindow::update directly here, as this is only allowed
        // from the rendering thread or GUI thread.
            emit pendingNewTexture();
        }


    // Before the scene graph starts to render, we update to the pending texture
        void prepareNode() {
            m_mutex.lock();
            int newId = m_id;
            QSize size = m_size;
            m_id = 0;
            m_mutex.unlock();
            if (newId) {
                delete m_texture;
            // note: include QQuickWindow::TextureHasAlphaChannel if the rendered content
            // has alpha.
                m_texture = m_window->createTextureFromId(newId, size);
                setTexture(m_texture);

                markDirty(DirtyMaterial);

            // This will notify the rendering thread that the texture is now being rendered
            // and it can start rendering to the other one.
                emit textureInUse();
            }
        }

    private:

        int m_id;
        QSize m_size;

        QMutex m_mutex;

        QSGTexture *m_texture;
        QQuickWindow *m_window;
    };

}





HDC::SceneRenderer::SceneRenderer()
: m_renderThread(nullptr)
{
    setFlag(ItemHasContents, true);
    m_renderThread = new SceneRenderThread(QSize(512, 512));
}

void HDC::SceneRenderer::ready()
{
    m_renderThread->surface = new QOffscreenSurface();
    m_renderThread->surface->setFormat(m_renderThread->context->format());
    m_renderThread->surface->create();

    m_renderThread->moveToThread(m_renderThread);

    connect(window(), &QQuickWindow::sceneGraphInvalidated, m_renderThread, &SceneRenderThread::shutDown, Qt::QueuedConnection);
    m_renderThread->start();
    update();
}

QSGNode *HDC::SceneRenderer::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
{
    TextureNode *node = static_cast<TextureNode *>(oldNode);

    if (!m_renderThread->context) {
        QOpenGLContext *current = window()->openglContext();
        // Some GL implementations requres that the currently bound context is
        // made non-current before we set up sharing, so we doneCurrent here
        // and makeCurrent down below while setting up our own context.
        current->doneCurrent();

        m_renderThread->context = new QOpenGLContext();
        QSurfaceFormat surfaceFormat;
        surfaceFormat.setVersion(3,1);
        surfaceFormat.setProfile(QSurfaceFormat::CoreProfile);
        m_renderThread->context->setFormat(surfaceFormat);
        m_renderThread->context->setShareContext(current);
        m_renderThread->context->create();
        m_renderThread->context->moveToThread(m_renderThread);

        current->makeCurrent(window());

        QMetaObject::invokeMethod(this, "ready");
        return nullptr;
    }

    if (!node) {
        node = new TextureNode(window());

        /* Set up connections to get the production of FBO textures in sync with vsync on the
         * rendering thread.
         *
         * When a new texture is ready on the rendering thread, we use a direct connection to
         * the texture node to let it know a new texture can be used. The node will then
         * emit pendingNewTexture which we bind to QQuickWindow::update to schedule a redraw.
         *
         * When the scene graph starts rendering the next frame, the prepareNode() function
         * is used to update the node with the new texture. Once it completes, it emits
         * textureInUse() which we connect to the FBO rendering thread's renderNext() to have
         * it start producing content into its current "back buffer".
         *
         * This FBO rendering pipeline is throttled by vsync on the scene graph rendering thread.
         */
        connect(m_renderThread, &SceneRenderThread::textureReady, node, &TextureNode::newTexture, Qt::DirectConnection);
        connect(node, &TextureNode::pendingNewTexture, window(), &QQuickWindow::update, Qt::QueuedConnection);
        connect(window(), &QQuickWindow::beforeRendering, node, &TextureNode::prepareNode, Qt::DirectConnection);
        connect(node, &TextureNode::textureInUse, m_renderThread, &SceneRenderThread::renderNext, Qt::QueuedConnection);

        // Get the production of FBO textures started..
        QMetaObject::invokeMethod(m_renderThread, "renderNext", Qt::QueuedConnection);
    }

    node->setRect(boundingRect());

    return node;
}

QString HDC::SceneRenderer::textureName(){
    return m_textureName;
}

void HDC::SceneRenderer::setTextureName(const QString& textureName){

    if (textureName == m_textureName){
        return;
    }
    m_textureName = textureName;
    auto ptrHeatmapRenderer = m_renderThread->getHeatmapRenderer();
    if (ptrHeatmapRenderer) {
        ptrHeatmapRenderer->loadTextureAndWrap(textureName);
    }
    emit textureNameChanged();
}
void HDC::SceneRenderer::keyPressed(int keypressed_code) {

    auto p = m_renderThread->getHeatmapRenderer();
    p->keyPressed(keypressed_code);

}
#include "threadrenderer.moc"
