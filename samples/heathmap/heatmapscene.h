#ifndef __HEATMAPREDNDERER_H__
#define __HEATMAPREDNDERER_H__
#include <QtGui/qvector3d.h>
#include <QtGui/qmatrix4x4.h>
#include <QtGui/qopenglshaderprogram.h>
#include <QtGui/qopenglfunctions.h>

#include <QTime>
#include <QEvent>
#include <QVector>
#include <QElapsedTimer>
#include <src/meshes/geometry120.h>
#include <src/camera/camera.h>
#include <src/texture/fastqtexturedata.h>

namespace HDC{
    class HeatmapRenderer : protected QObject, QOpenGLFunctions
    {
        Q_OBJECT
    public:
        HeatmapRenderer(QObject* parent = nullptr);
        ~HeatmapRenderer();

        void render();
        void initialize();
        void loadTextureAndWrap(const QString &rTexturePath);
        void leftPressed(QEvent::Type);
        void rightPressed(QEvent::Type);
    protected:
        bool event(QEvent *event ) override ;
    private:
        void initializeTextures();

        void paintQtLogo();
        void createGeometry();


        bool textureChanged{false};
        HDC::Camera m_cam;
        HDC::Plane120 plane;
        HDC::FastQTextureData* m_soccer_court_texture{nullptr};
        QOpenGLShaderProgram program1;

        int matrixUniform1;
        int courtUniform;

        QElapsedTimer* m_ptimer{nullptr};

    };
}

#endif /* __HEATMAPREDNDERER_H__
 */
