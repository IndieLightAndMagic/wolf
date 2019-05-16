#include "heatmapscene.h"


#include <QPainter>
#include <QPaintEngine>
#include <qmath.h>

HDC::HeatmapRenderer::HeatmapRenderer()
{
}

HDC::HeatmapRenderer::~HeatmapRenderer()
{
}


void HDC::HeatmapRenderer::paintQtLogo()
{
    auto va = plane.getvertexattr();
    auto pdata = plane.getvertexdata();
    program1.enableAttributeArray(va);
    program1.setAttributeArray(va, pdata, 3, 0);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    program1.disableAttributeArray(va);
}

void HDC::HeatmapRenderer::initializeTextures(){

    

}
void HDC::HeatmapRenderer::initialize()
{
    initializeOpenGLFunctions();

    glClearColor(0.1f, 0.1f, 0.2f, 1.0f);

    
    program1.addCacheableShaderFromSourceFile(QOpenGLShader::Vertex, QString::fromStdString(std::string{RESOURCES_DIR} + "/shaders/heatmap_t.vert"));
    program1.addCacheableShaderFromSourceFile(QOpenGLShader::Fragment, QString::fromStdString(std::string{RESOURCES_DIR} + "/shaders/heatmap_t.frag"));
    program1.link();

    auto& vertexAttr1 = plane.getvertexattr();
    vertexAttr1 = program1.attributeLocation("vertex");
    matrixUniform1 = program1.uniformLocation("matrix");


    m_cam.setCamera();

    createGeometry();

}

void HDC::HeatmapRenderer::render()
{
    glDepthMask(true);

    glClearColor(0.5f, 0.5f, 0.7f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glEnable(GL_DEPTH_TEST);

    program1.bind();


    m_cam.setCameraPositionDelta(0.0f, 0.0f, -.10f);
    auto mtx = m_cam.getCamera();
    program1.setUniformValue(matrixUniform1, mtx);
    paintQtLogo();
    program1.release();

    glDisable(GL_DEPTH_TEST);


}

void HDC::HeatmapRenderer::createGeometry()
{
    auto size = 10.0f;
    plane.setsize(size*1.05f, size*.68f);


}


