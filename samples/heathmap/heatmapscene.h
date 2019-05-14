#ifndef _INTROSCENE_H_
#define _INTROSCENE_H_

#include "scene.h"
#include "camera.h"
#include "shader.h"
#include "geometry.h"
#include "fastqtexturedata.h"
#include "fastclampedtexturedata.h"
#include "heatmapplayer.h"

#include <memory>
#include <QImage>
#include <QtCore/QElapsedTimer>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QOpenGLFunctions>
#include <QtGui/QOpenGLFunctions_4_3_Core>


namespace HDC{
    class HeatMapScene : public Scene
    {
    public:
        HDC::HeatMapPlayer* m_heatmapplayer;
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
        
        HeatMapScene();

        void initialize() override;
        void render() override;

    private:
        void initializeShader();
        void initializeTextures();
        void initializeGeometry();
        void handleEscape();
        void handleUp();
        void handleDown();
        void handleWheel(int);
        void handleWheelButton();


        GLuint m_matrixUniform;
        HDC::FastQTextureData* m_soccer_court_texture{nullptr}; //ARGB [0 = B, G = 1, R = 2, A = 3]

        unsigned int m_court_textureUniform;
        unsigned int m_heat__textureUniform;
        GLuint m_blendSliderUniform;
        GLuint m_fgridSliderUniform;


        HDC::TexturedPlaneGeometry* m_soccer_court{nullptr};

        std::shared_ptr<HDC::ShaderProgram> shaderProgram{nullptr};
        QOpenGLShaderProgram* fastShaderProgram;

        QElapsedTimer m_timer;
        uint64_t m_elapsedTimeMeasurement{0};

        HeatMapScene::IntroState m_state{IntroState::START};
        HeatMapScene::WheelState m_wheelstate{WheelState::BLEND};
        float m_timeToExpire{0.0f};
        unsigned int m_activeTextureIndex{0};

        unsigned int grid_exponent{0};
        float m_fgrid{1.0f};
        float m_fblend{1.0f};

        
    };
}
#endif /* _INTROSCENE_H_ */
