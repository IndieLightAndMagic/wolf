#ifndef _INTROSCENE_H_
#define _INTROSCENE_H_

#include "camera.h"
#include "shader.h"
#include "geometry.h"
#include "inputmanager.h"
#include "fastqtexturedata.h"
#include "fastclampedtexturedata.h"
#include "heatmapplayer.h"

#include <QObject>
#include <QScopedPointer>

#include <QImage>

#include <QtCore/QElapsedTimer>

class QOpenGLBuffer;
class QOpenGLShaderProgram;
class QOpenGLVertexArrayObject;

namespace HDC{
    class HeatMapScene : public QObject
    {
        Q_OBJECT
    public:
        explicit HeatMapScene(QObject* parent = 0);
        ~HeatMapScene();

        HDC::HeatMapPlayer* m_heatmapplayer;
        Camera m_cam;


        void initialize();
        void render();
        void invalidate();

        void setdistance(float distance);

    private:
        void initializeShader();
        void initializeTextures();
        void initializeGeometry();

        GLuint m_matrixUniform;
        HDC::FastQTextureData* m_soccer_court_texture{nullptr}; //ARGB [0 = B, G = 1, R = 2, A = 3]

        unsigned int m_court_textureUniform;
        unsigned int m_heat__textureUniform;
        GLuint m_blendSliderUniform;
        GLuint m_fgridSliderUniform;


        HDC::TexturedPlaneGeometry* m_soccer_court{nullptr};

        std::shared_ptr<HDC::ShaderProgram> shaderProgram{nullptr};
        QOpenGLShaderProgram* fastShaderProgram;



        float m_fblend{1.0f};
        float m_distance{1.0f};
        
    };
}
#endif /* _INTROSCENE_H_ */
