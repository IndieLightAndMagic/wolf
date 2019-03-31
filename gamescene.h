#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__
#include "scene.h"
#include "camera.h"
#include "resources/atlases/level_compressed.png.h"
#include <memory>
#include <QtGui/QOpenGLShaderProgram>



class GameScene : public Scene
{
public:
    Camera m_cam;
    __level_compressed_png_level1 level1_data;
    unsigned char* m_atlas_data;
    float selector{0.0};
    GameScene();

    void initialize() override;
    void render() override;

private:

    void initializeShaders(QOpenGLShader::ShaderType type, const char* path);
    void initializeGeometry();
    void bakeShader();
    void handleEscape();
    void handleRight();
    void handleLeft();
    GLuint m_posAttr;
    GLuint m_colAttr;
    GLuint m_texAttr;
    GLuint m_matrixUniform;
    GLuint m_vao, m_vbo, m_ebo, m_ubo, m_ubo_uniformblockindex, m_p_selector;

    QOpenGLShaderProgram *m_program{nullptr};




};
#endif /* __GAMESCENE_H__ */
