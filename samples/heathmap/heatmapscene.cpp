#include "heatmapscene.h"

#include <QDebug>
#include <QPainter>
#include <QKeyEvent>
#include <QPaintEngine>
#include <qmath.h>
#include <src/texture/fasttexturedata.h>
#include "src/texture/fastqtexturedata.h"

constexpr auto _6gradsPerSec__ms__ = 0.006f;
static auto zRotation = 0.0f;
static auto zRotationSpeedDegPerMs = 0.000f;//6.0f Grad Per /1000.0f Millisecs //AKA 6 grad per sec;

constexpr auto _1meter = 0.01f;
constexpr auto _1meterpersec__ms__ = _1meter / 1000;
static auto zSpeedMeterPerMs = 0.000f;

QQE::HeatmapRenderer::HeatmapRenderer(QObject* parent):ECS_SYSTEM::Renderer(parent)
{

    m_ptimer = new QElapsedTimer();
    m_ptimer->start();

}

QQE::HeatmapRenderer::~HeatmapRenderer()
{
    delete m_ptimer;
}
void QQE::HeatmapRenderer::loadTextureAndWrap(const QString &rTexturePath) {


    auto sz = rTexturePath.size();
    sz -= QString{"file://"}.size();

    auto file_absolutepath = rTexturePath.right(sz);
    qDebug() << "Ok The Scene recieved: " << file_absolutepath;
    QImage* pqimg = new QImage(file_absolutepath);

    if (pqimg) {

        if (m_soccer_court_texture){

            delete m_soccer_court_texture;
            m_soccer_court_texture = nullptr;

        }
        m_soccer_court_texture  = new QQE::FastQTextureData(pqimg);
    }

}

void QQE::HeatmapRenderer::paintQtLogo()
{
    auto vertices      = QQE::Plane120::Plane120Attr::vertices;
    auto texturecoords = QQE::Plane120::Plane120Attr::texturecoords;
    
    auto vertexattrlocation = plane.getattrlocation(vertices);
    auto tcoordattrlocation = plane.getattrlocation(texturecoords);
    
    auto vertexdata = plane.getdata(vertices);
    auto tcoorddata = plane.getdata(texturecoords);
    
    program1.enableAttributeArray(vertexattrlocation);
    program1.setAttributeArray(vertexattrlocation, vertexdata, 3, 0);
    
    program1.enableAttributeArray(tcoordattrlocation);
    program1.setAttributeArray(tcoordattrlocation, tcoorddata, 2, 0);

    m_soccer_court_texture->updateTexture();
    program1.setUniformValue(courtUniform, m_soccer_court_texture->gl.slot);
    m_soccer_court_texture->bind();

    auto glFuncs = QOpenGLContext::currentContext()->functions();
    glFuncs->glDrawArrays(GL_TRIANGLES, 0, 6);

    program1.disableAttributeArray(tcoordattrlocation);
    program1.disableAttributeArray(vertexattrlocation);
}

void QQE::HeatmapRenderer::initializeTextures(){

    QImage* pqimg = new QImage(QString::fromStdString(std::string{RESOURCES_DIR} + "/textures/soccer_court_texture.png"));
    m_soccer_court_texture  = new QQE::FastQTextureData(pqimg);

}
void QQE::HeatmapRenderer::initialize()
{


    program1.addCacheableShaderFromSourceFile(QOpenGLShader::Vertex, QString::fromStdString(std::string{RESOURCES_DIR} + "/shaders/heatmap_t.vert"));
    program1.addCacheableShaderFromSourceFile(QOpenGLShader::Fragment, QString::fromStdString(std::string{RESOURCES_DIR} + "/shaders/heatmap_t.frag"));
    program1.link();

    createGeometry();
    
    
    matrixUniform1 = program1.uniformLocation("matrix");
    courtUniform   = program1.uniformLocation("court_texture");

    m_cam.setCamera();

    initializeTextures();

}



void QQE::HeatmapRenderer::render()
{
    static auto tFrame = qint64{0};
    static auto tBegin = qint64{0};


    auto tNow = m_ptimer->elapsed();

    if (tBegin == 0.0f){

        tBegin = tFrame = tNow;
        return;

    }

    auto timeDelta = tNow - tBegin;
    zRotation += zRotationSpeedDegPerMs * timeDelta;
    auto zDelta = zSpeedMeterPerMs * timeDelta; 
    tBegin = tNow;

    auto glFuncs = QOpenGLContext::currentContext()->functions();

    glFuncs->glDepthMask(true);

    glFuncs->glClearColor(0.0f, 0.5f, 0.7f, 1.0f);
    glFuncs->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //glEnable(GL_DEPTH_TEST);



    program1.bind();
    {

        m_cam.setCameraPositionDelta(0.0f, 0.0f, zDelta);

        auto mtxReference = m_cam.getCamera();
        mtxReference.rotate(75.0f, 1.0f, 0.0f, 0.0f);
        mtxReference.rotate(zRotation, 0.0, 0.0, 1.0f);

        program1.setUniformValue(matrixUniform1, mtxReference);
        paintQtLogo();
    
    }

    program1.release();




    //glDisable(GL_DEPTH_TEST);


}

void QQE::HeatmapRenderer::createGeometry()
{
    plane.reset(1.05, .68);
    plane.setattrlocation(program1.attributeLocation("vertex"), QQE::Plane120::Plane120Attr::vertices);
    plane.setattrlocation(program1.attributeLocation("texcoord"), QQE::Plane120::Plane120Attr::texturecoords);
}

void QQE::HeatmapRenderer::keyPressed(int keypressed_code){

    if (keypressed_code == Qt::Key_Left){

        leftPressed();

    } else if(keypressed_code == Qt::Key_Right){

        rightPressed();

    } else if (keypressed_code == Qt::Key_Down){

        downPressed();

    } else if (keypressed_code == Qt::Key_Up) {

        upPressed();

    }
    //qDebug() << "Key Pressed " << keymsg << " " <<__FILE__ << " : " << __LINE__ ;

}
void QQE::HeatmapRenderer::leftPressed() {

    zRotationSpeedDegPerMs = zRotationSpeedDegPerMs <= 0.0f ? _6gradsPerSec__ms__ * 10 : 0.0f;

}
void QQE::HeatmapRenderer::rightPressed() {

    zRotationSpeedDegPerMs = zRotationSpeedDegPerMs >= 0.0f ? -_6gradsPerSec__ms__ * 10 : 0.0f;

}
void QQE::HeatmapRenderer::upPressed() {

    zSpeedMeterPerMs = zSpeedMeterPerMs <= 0.0f ? _1meterpersec__ms__ * 10 : 0.0f;

}
void QQE::HeatmapRenderer::downPressed() {

    zSpeedMeterPerMs = zSpeedMeterPerMs >= 0.0f ? -_1meterpersec__ms__ * 10 : 0.0f;

}

bool QQE::HeatmapRenderer::event( QEvent* event )
{

    auto et = event->type();
    if( et == QEvent::KeyPress || et == QEvent::KeyRelease){
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>( event );

        if ( keyEvent->key() == Qt::Key_Up ) { return true;}
        else if ( keyEvent->key() == Qt::Key_Down ) { return true;}
        else if ( keyEvent->key() == Qt::Key_Left ) {

            return true;
        }
        else if ( keyEvent->key() == Qt::Key_Right ) {

            return true;
        }
        else if ( keyEvent->key() == Qt::Key_Escape ) { return true;}


    }

    return false;
}
