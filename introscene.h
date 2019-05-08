#ifndef _INTROSCENE_H_
#define _INTROSCENE_H_

#include "scene.h"
#include "camera.h"
#include "shader.h"
#include "texturemanager.h"
#include "meshes/geometry.h"


#include <memory>
#include <QImage>
#include <QtCore/QElapsedTimer>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QOpenGLFunctions>
#include <QtGui/QOpenGLFunctions_4_3_Core>


namespace HDC{
    class IntroScene : public Scene
    {
    public:
        Camera m_cam;
        enum class IntroState {
            START, 
            FADING_IN_CARNAGE, 
            STILL_IN_CARNAGE, 
            FADING_OUT_CARNAGE, 
            FADING_CLASSIC_IN, 
            STILL_IN_CLASSIC, 
            FADING_OUT_CLASSIC,
            IDLE,
            FINISH
        };

        QImage qimage{};
        std::vector<QImage> qimages{};
        
        IntroScene();

        void initialize() override;
        void render() override;

    private:

        void processState();
        void initializeShaders(QOpenGLShader::ShaderType type, const char* path);
        void bakeShader();
        void initializeGeometry();
        void handleEscape();
        void handleUp();
        void handleDown();

        GLuint m_posAttr;
        GLuint m_colAttr;
        GLuint m_texAttr;
        GLuint m_matrixUniform;
        GLuint m_textureUniform;
        GLuint m_pcsSliderUniform;
        
        GLuint m_soccer_court_texture;
        HDC::TexturedPlane m_soccer_court{HDC::TexturedPlane::getplane()};

        std::shared_ptr<HDC::ShaderProgram> shaderProgram;
        QOpenGLShaderProgram* fastShaderProgram;

        QElapsedTimer m_timer;
        uint64_t m_elapsedTimeMeasurement{0};

        IntroScene::IntroState m_state{IntroState::START};
        float m_timeToExpire{0.0f};
        unsigned int m_activeTextureIndex{0};

    };
}
#endif /* _INTROSCENE_H_ */
