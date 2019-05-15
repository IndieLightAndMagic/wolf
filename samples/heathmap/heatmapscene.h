#ifndef __HEATMAPREDNDERER_H__
#define __HEATMAPREDNDERER_H__
#include <QtGui/qvector3d.h>
#include <QtGui/qmatrix4x4.h>
#include <QtGui/qopenglshaderprogram.h>
#include <QtGui/qopenglfunctions.h>

#include <QTime>
#include <QVector>
#include <src/meshes/geometry.h>
#include <src/camera/camera.h>

namespace HDC{
    class HeatmapRenderer : protected QOpenGLFunctions
    {
    public:
        HeatmapRenderer();
        ~HeatmapRenderer();

        void render();
        void initialize();

    private:

        qreal   m_fAngle;
        qreal   m_fScale;

        void paintQtLogo();
        void createGeometry();
        void quad(qreal x1, qreal y1, qreal x2, qreal y2, qreal x3, qreal y3, qreal x4, qreal y4);
        void extrude(qreal x1, qreal y1, qreal x2, qreal y2);

        HDC::Camera m_cam;
        HDC::PlaneGeometry120 plane;
        QVector<QVector3D> vertices;
        QVector<QVector3D> normals;
        QOpenGLShaderProgram program1;
        //int vertexAttr1;
        //int normalAttr1;
        int matrixUniform1;


    };
}

#endif /* __HEATMAPREDNDERER_H__
 */
