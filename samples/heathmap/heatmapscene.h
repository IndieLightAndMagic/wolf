#ifndef __HEATMAPREDNDERER_H__
#define __HEATMAPREDNDERER_H__
#include <QtGui/qvector3d.h>
#include <QtGui/qmatrix4x4.h>
#include <QtGui/qopenglshaderprogram.h>
#include <QtGui/qopenglfunctions.h>

#include <QTime>
#include <QVector>
#include <src/meshes/geometry120.h>
#include <src/camera/camera.h>
#include <src/texture/fastqtexturedata.h>

namespace HDC{
    class HeatmapRenderer : protected QOpenGLFunctions
    {
    public:
        HeatmapRenderer();
        ~HeatmapRenderer();

        void render();
        void initialize();
        void loadTextureAndWrap(const QString &rTexturePath);

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


    };
}

#endif /* __HEATMAPREDNDERER_H__
 */
