#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__
#include "scene.h"
#include "camera.h"
#include <memory>
#include <QImage>
#include <QtCore/QElapsedTimer>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QOpenGLFunctions>
#include <QtGui/QOpenGLFunctions_4_3_Core>

class GameScene : public Scene
{
public:
    Camera m_cam;
    
    std::shared_ptr<unsigned char> ptrCodeBuffer{nullptr};
    
    GameScene();

    void initialize() override;
    void render() override;

private:

    void initializeShaders(QOpenGLShader::ShaderType type, const char* path);
    void initializeGeometry();
    void handleEscape();
    
    GLuint m_posAttr;
    GLuint m_colAttr;
    GLuint m_texAttr;
    GLuint m_matrixUniform;
    GLuint m_vao, m_vbo, m_ebo;

    QOpenGLShaderProgram *m_program{nullptr};




};
#endif /* __GAMESCENE_H__ */
