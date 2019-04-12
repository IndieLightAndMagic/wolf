#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "scene.h"
#include "shader.h"
#include "camera.h"

#include <tuple>
#include <vector>

#include <QImage>
#include <QRectF>


namespace HDC {

    class TextureAtlas : public QImage {

        unsigned int m_gridWidth{1u};
        unsigned int m_gridHeight{1u};

        std::vector<unsigned int> m_tbos;

    public:
        TextureAtlas(const QImage& rimage, unsigned int gridWidth, unsigned int gridHeight) : QImage(rimage){
            m_gridWidth = gridWidth;
            m_gridHeight = gridHeight; 
        }
        TextureAtlas(){}

    };


    class GameScene : public Scene
    {
    public:
        Camera m_cam;

        GameScene();
        void initialize() override;
        void render() override;

    private:
        void initializeGeometry();
        void handleEscape();
        void handleRight();
        void handleLeft();
        GLuint m_posAttr;
        GLuint m_colAttr;
        GLuint m_texAttr;
        GLuint m_matrixUniform;
        GLuint m_vao, m_vbo, m_ebo, m_ubo, m_ubo_uniformblockindex, m_p_selector;

        ShaderProgram shaderProgram;
        float selector{0.0f};
    };

}

#endif /* __GAMESCENE_H__ */
