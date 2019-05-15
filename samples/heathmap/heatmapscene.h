#ifndef __HEATMAPREDNDERER_H__
#define __HEATMAPREDNDERER_H__


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
    class HeatmapRenderer : public QOpenGLFunctions
    {

    public:
        HeatmapRenderer();
        ~HeatmapRenderer();

        void render();
        void initialize();

    private:
        
        Camera m_cam;


        void initializeShader();
        void initializeTextures();
        void initializeGeometry();

        GLuint m_matrixUniform;
        unsigned int m_court_textureUniform;
        unsigned int m_heat__textureUniform;
        unsigned int m_blendSliderUniform;
        unsigned int m_fgridSliderUniform;


        HDC::TexturedPlaneGeometry* m_soccer_court{nullptr};
        HDC::FastQTextureData* m_soccer_court_texture{nullptr}; //ARGB [0 = B, G = 1, R = 2, A = 3]

        std::shared_ptr<HDC::ShaderProgram> shaderProgram{nullptr};
        QOpenGLShaderProgram* fastShaderProgram;



        HDC::HeatMapPlayer* m_heatmapplayer;
        float m_fblend{1.0f};
        
        
    };
}
#endif /* __HEATMAPREDNDERER_H__
 */
