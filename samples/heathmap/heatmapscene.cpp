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

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );


    auto& mtx = m_cam.getCamera();
    mtx.rotate(-50.0f, QVector3D(1.0f, 0.0f, 0.0f));
    m_cam.setCameraPosition(0.0f, 0.0f, -12.0f);

    createGeometry();

}

void HDC::HeatmapRenderer::render()
{
    glDepthMask(true);

    glClearColor(0.5f, 0.5f, 0.7f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    glEnable(GL_DEPTH_TEST);

    program1.bind();
    program1.setUniformValue(matrixUniform1, m_cam.getCamera());
    paintQtLogo();
    program1.release();

    glDisable(GL_DEPTH_TEST);


}

void HDC::HeatmapRenderer::createGeometry()
{
    plane.resetplane();

}


