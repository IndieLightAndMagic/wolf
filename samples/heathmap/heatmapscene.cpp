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
    //program1.enableAttributeArray(normalAttr1);
    auto va = plane.getvertexattr();
    auto pdata = plane.getvertexdata();

    program1.enableAttributeArray(va);
    program1.setAttributeArray(va, pdata, 3, 0);

    //std::cout << vertices[0].x() << "  " << vertices[0].y() << " " << vertices[0].z() <<  std::endl;
    //std::cout << pdata[0] << "  " << pdata[1] << " " << pdata[2] <<  std::endl;
    //std::cout << pdata[3] << "  " << pdata[4] << " " << pdata[5] <<  std::endl;
    //std::cout << pdata[6] << "  " << pdata[7] << " " << pdata[8] <<  std::endl;

    //program1.setAttributeArray(normalAttr1, normals.constData());
    glDrawArrays(GL_TRIANGLES, 0, 3);
    //program1.disableAttributeArray(normalAttr1);
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
    //normalAttr1 = program1.attributeLocation("normal");
    matrixUniform1 = program1.uniformLocation("matrix");

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    m_fAngle = 0;
    m_fScale = 1;

    createGeometry();

}

void HDC::HeatmapRenderer::render()
{
    glDepthMask(true);

    glClearColor(0.5f, 0.5f, 0.7f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    glFrontFace(GL_CW);
    glCullFace(GL_FRONT);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    m_cam.setCameraPosition(0.0f, 0.0f, -5.0f);
    QMatrix4x4& modelview = m_cam.getCamera();

    program1.bind();
    program1.setUniformValue(matrixUniform1, modelview);
    paintQtLogo();
    program1.release();

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    m_fAngle += 0.0f;
}

void HDC::HeatmapRenderer::createGeometry()
{
    vertices.clear();
    normals.clear();

    qreal x1 = +0.06f;
    qreal y1 = -0.14f;
    qreal x2 = +0.14f;
    qreal y2 = -0.06f;
    qreal x3 = +0.08f;
    qreal y3 = +0.00f;
    qreal x4 = +0.30f;
    qreal y4 = +0.22f;

    quad(x1, y1, x2, y2, y2, x2, y1, x1);
    quad(x3, y3, x4, y4, y4, x4, y3, x3);

    extrude(x1, y1, x2, y2);
    extrude(x2, y2, y2, x2);
    extrude(y2, x2, y1, x1);
    extrude(y1, x1, x1, y1);
    extrude(x3, y3, x4, y4);
    extrude(x4, y4, y4, x4);
    extrude(y4, x4, y3, x3);

    const qreal Pi = M_PI;
    const int NumSectors = 100;

    for (int i = 0; i < NumSectors; ++i) {
        qreal angle1 = (i * 2 * Pi) / NumSectors;
        qreal x5 = 0.30 * sin(angle1);
        qreal y5 = 0.30 * cos(angle1);
        qreal x6 = 0.20 * sin(angle1);
        qreal y6 = 0.20 * cos(angle1);

        qreal angle2 = ((i + 1) * 2 * Pi) / NumSectors;
        qreal x7 = 0.20 * sin(angle2);
        qreal y7 = 0.20 * cos(angle2);
        qreal x8 = 0.30 * sin(angle2);
        qreal y8 = 0.30 * cos(angle2);

        quad(x5, y5, x6, y6, x7, y7, x8, y8);

        extrude(x6, y6, x7, y7);
        extrude(x8, y8, x5, y5);
    }
    auto pdata = plane.getvertexdata();
    for (int i = 0;i < vertices.size();i++) {
        vertices[i] *= 2.0f;
        if (i < 2){
            pdata[i * 3 + 0] = vertices[i].x();
            pdata[i * 3 + 1] = vertices[i].y();
            pdata[i * 3 + 2] = vertices[i].z();

        }
    }
}

void HDC::HeatmapRenderer::quad(qreal x1, qreal y1, qreal x2, qreal y2, qreal x3, qreal y3, qreal x4, qreal y4)
{
    vertices << QVector3D(x1, y1, -0.05f);
    vertices << QVector3D(x2, y2, -0.05f);
    vertices << QVector3D(x4, y4, -0.05f);

    vertices << QVector3D(x3, y3, -0.05f);
    vertices << QVector3D(x4, y4, -0.05f);
    vertices << QVector3D(x2, y2, -0.05f);

    QVector3D n = QVector3D::normal
    (QVector3D(x2 - x1, y2 - y1, 0.0f), QVector3D(x4 - x1, y4 - y1, 0.0f));

    normals << n;
    normals << n;
    normals << n;

    normals << n;
    normals << n;
    normals << n;

    vertices << QVector3D(x4, y4, 0.05f);
    vertices << QVector3D(x2, y2, 0.05f);
    vertices << QVector3D(x1, y1, 0.05f);

    vertices << QVector3D(x2, y2, 0.05f);
    vertices << QVector3D(x4, y4, 0.05f);
    vertices << QVector3D(x3, y3, 0.05f);

    n = QVector3D::normal
    (QVector3D(x2 - x4, y2 - y4, 0.0f), QVector3D(x1 - x4, y1 - y4, 0.0f));

    normals << n;
    normals << n;
    normals << n;

    normals << n;
    normals << n;
    normals << n;
}

void HDC::HeatmapRenderer::extrude(qreal x1, qreal y1, qreal x2, qreal y2)
{
    vertices << QVector3D(x1, y1, +0.05f);
    vertices << QVector3D(x2, y2, +0.05f);
    vertices << QVector3D(x1, y1, -0.05f);

    vertices << QVector3D(x2, y2, -0.05f);
    vertices << QVector3D(x1, y1, -0.05f);
    vertices << QVector3D(x2, y2, +0.05f);

    QVector3D n = QVector3D::normal
    (QVector3D(x2 - x1, y2 - y1, 0.0f), QVector3D(0.0f, 0.0f, -0.1f));

    normals << n;
    normals << n;
    normals << n;

    normals << n;
    normals << n;
    normals << n;
}

