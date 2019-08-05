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
#include "ecs/systems/render.h"

namespace QQE{
class HeatmapRenderer : public ECS_SYSTEM::Renderer
    {
        Q_OBJECT
    public:
        HeatmapRenderer(QObject* parent = nullptr);
        ~HeatmapRenderer();

        void render() override;
        void initialize() override;
        void loadTextureAndWrap(const QString &rTexturePath);

        void keyPressed(int keypressed_code);
        void leftPressed();
        void rightPressed();
        void upPressed();
        void downPressed();

    protected:
        bool event(QEvent *event ) override ;
    private:
        void initializeTextures();

        void paintQtLogo();
        void createGeometry();


        bool textureChanged{false};
        QQE::Camera m_cam;
        QQE::Plane120 plane;
        QQE::FastQTextureData* m_soccer_court_texture{nullptr};
        QOpenGLShaderProgram program1;

        int matrixUniform1;
        int courtUniform;

        QElapsedTimer* m_ptimer{nullptr};

    };
}

#endif /* __HEATMAPREDNDERER_H__
 */
