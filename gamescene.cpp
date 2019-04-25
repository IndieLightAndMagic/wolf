#include "gamescene.h"
#include "shader.h"

#include <iostream>
#include <memory>
#include <string>
#include <tuple>
#include <vector>

char vertBuffer[4096];
char fragBuffer[4096];


HDC::GameScene::GameScene(){
    
}


void HDC::GameScene::initializeGeometry(){

    float vertices[] = {
        // positions                // colors           
         0.5000f,  0.3125f, -1.0f,   1.0f, 0.0f, 0.0f,    1.0f,  1.0f,// top right
         0.5000f, -0.3125f, -1.0f,   0.0f, 1.0f, 0.0f,    1.0f,  0.0f,// bottom right
        -0.5000f, -0.3125f, -1.0f,   0.0f, 0.0f, 1.0f,    0.0f,  0.0f,// bottom left
        -0.5000f,  0.3125f, -1.0f,   1.0f, 1.0f, 0.0f,    0.0f,  1.0f // top left 
    };
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);    
    glGenBuffers(1, &m_ebo);

    glBindVertexArray(m_vao);
    
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);    

    // color attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);    

}

void HDC::GameScene::initialize(){

    initializeGeometry();
    auto bOk = shaderProgram.AddShader(HDC::ShaderType::VTX, "/shaders/level1.vert");
    if (bOk) bOk = shaderProgram.AddShader(HDC::ShaderType::FRG, "/shaders/level1.frag");
    if (!bOk) return;
    //qimage = TextureManagerQT::initializeTexture(TextureManager::solvePath(ppath));

    auto program = shaderProgram.GetProgram();
    
    m_matrixUniform = program->uniformLocation("matrix");
    m_p_selector = program->uniformLocation("spriteselector");

    m_cam.setCamera();

    installEventFilter(&m_im);
    connect(&m_im, &InputManager::escape, this, &HDC::GameScene::handleEscape);
    connect(&m_im, &InputManager::right_arrow, this, &HDC::GameScene::handleRight);
    connect(&m_im, &InputManager::left_arrow, this, &HDC::GameScene::handleLeft);

}

void HDC::GameScene::render(){

    Scene::render();

    shaderProgram.GetProgram()->bind();
    glBindVertexArray(m_vao);
    shaderProgram.GetProgram()->setUniformValue(m_matrixUniform, m_cam.getCamera());
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    shaderProgram.GetProgram()->release();

}


void HDC::GameScene::handleRight(){
    selector+=1;
    if (selector >= 10) selector = 0;
    std::cout << "Selector: " << (int)selector << std::endl;
}
void HDC::GameScene::handleLeft(){
    selector -= 1;
    if (selector < 0) selector = 10;
    std::cout << "Selector: " << (int)selector << std::endl;
}

void HDC::GameScene::handleEscape(){
    std::cout << "Finishing Scene....." << std::endl;
    QCoreApplication::exit(0);
}
