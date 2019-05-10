#ifndef _INTROSCENE_H_
#define _INTROSCENE_H_

#include "scene.h"
#include "camera.h"
#include "shader.h"
#include "geometry.h"
#include "texturemanager.h"


#include <memory>
#include <QImage>
#include <QtCore/QElapsedTimer>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QOpenGLFunctions>
#include <QtGui/QOpenGLFunctions_4_3_Core>


namespace HDC{
    class HeathMap : public Scene
    {
    public:
        Camera m_cam;
        enum class WheelState {
            GRID,
            BLEND
        };
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
        
        HeathMap();

        void initialize() override;
        void render() override;

    private:

        void initializeTextures();
        void initializeGeometry();
        void handleEscape();
        void handleUp();
        void handleDown();
        void handleWheel(int);
        void handleWheelButton();


        GLuint m_matrixUniform;
        GLuint m_court_textureUniform;
        GLuint m_heat__textureUniform;
        GLuint m_blendSliderUniform;
        GLuint m_fgridSliderUniform;
        HDC::FastTextureData *m_soccer_court_texture;
        HDC::FastTextureData *m_heatmap_texture;

        HDC::TexturedPlaneGeometry* m_soccer_court{nullptr};

        std::shared_ptr<HDC::ShaderProgram> shaderProgram;
        QOpenGLShaderProgram* fastShaderProgram;

        QElapsedTimer m_timer;
        uint64_t m_elapsedTimeMeasurement{0};

        HeathMap::IntroState m_state{IntroState::START};
        HeathMap::WheelState m_wheelstate{WheelState::GRID};
        float m_timeToExpire{0.0f};
        unsigned int m_activeTextureIndex{0};

        unsigned int grid_exponent{0};
        float m_fgrid{1.0f};
        float m_fblend{0.0f};

        
    };
}
#endif /* _INTROSCENE_H_ */
