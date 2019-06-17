#include "heatmapscene.h"

#include <QDebug>
#include <QPainter>
#include <QPaintEngine>
#include <qmath.h>
#include <src/texture/fasttexturedata.h>
#include "src/texture/fastqtexturedata.h"

HDC::HeatmapRenderer::HeatmapRenderer(QObject* parent):QObject(parent)
{
    m_ptimer = new QElapsedTimer();
    m_ptimer->start();
}

HDC::HeatmapRenderer::~HeatmapRenderer()
{
    delete m_ptimer;
}
void HDC::HeatmapRenderer::loadTextureAndWrap(const QString &rTexturePath) {


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
        m_soccer_court_texture  = new HDC::FastQTextureData(pqimg);
    }

}

void HDC::HeatmapRenderer::paintQtLogo()
{
    auto vertices      = HDC::Plane120::Plane120Attr::vertices;
    auto texturecoords = HDC::Plane120::Plane120Attr::texturecoords;
    
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

    glDrawArrays(GL_TRIANGLES, 0, 6);

    program1.disableAttributeArray(tcoordattrlocation);
    program1.disableAttributeArray(vertexattrlocation);
}

void HDC::HeatmapRenderer::initializeTextures(){

    QImage* pqimg = new QImage(QString::fromStdString(std::string{RESOURCES_DIR} + "/textures/soccer_court_texture.png"));
    m_soccer_court_texture  = new HDC::FastQTextureData(pqimg);

}
void HDC::HeatmapRenderer::initialize()
{

    initializeOpenGLFunctions();

    glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
    
    program1.addCacheableShaderFromSourceFile(QOpenGLShader::Vertex, QString::fromStdString(std::string{RESOURCES_DIR} + "/shaders/heatmap_t.vert"));
    program1.addCacheableShaderFromSourceFile(QOpenGLShader::Fragment, QString::fromStdString(std::string{RESOURCES_DIR} + "/shaders/heatmap_t.frag"));
    program1.link();

    createGeometry();
    
    
    matrixUniform1 = program1.uniformLocation("matrix");
    courtUniform   = program1.uniformLocation("court_texture");

    m_cam.setCamera();

    initializeTextures();

}

constexpr bool frameperiodexpired(qint64 tDelta, const qint64 tFramePeriod = 33){
    if (tDelta > tFramePeriod) return true;
    return false;
}

void HDC::HeatmapRenderer::render()
{
    static auto tFrame = qint64{0};
    static auto tBegin = qint64{0};

    static auto zRotation = 0.0f;
    const auto  zRotationSpeedDegPerMs = 0.006f;//6.0f Grad Per /1000.0f Millisecs //AKA 6 grad per sec;

    auto tNow = m_ptimer->elapsed();

    if (tBegin == 0.0f){

        tBegin = tFrame = tNow;
        return;

    }

    zRotation = zRotationSpeedDegPerMs * (tNow - tBegin);

    glDepthMask(true);

    glClearColor(0.0f, 0.5f, 0.7f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //glEnable(GL_DEPTH_TEST);



    program1.bind();
    {
        auto mtx = m_cam.getCamera();
        mtx.rotate(zRotation, 0.0, 0.0, 1.0f);
        program1.setUniformValue(matrixUniform1, mtx);
        paintQtLogo();
    }
    program1.release();




    //glDisable(GL_DEPTH_TEST);


}

void HDC::HeatmapRenderer::createGeometry()
{
    plane.reset(1.05, .68);
    plane.setattrlocation(program1.attributeLocation("vertex"), HDC::Plane120::Plane120Attr::vertices);
    plane.setattrlocation(program1.attributeLocation("texcoord"), HDC::Plane120::Plane120Attr::texturecoords);
    
}


