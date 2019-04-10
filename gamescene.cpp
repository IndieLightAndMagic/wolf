#include "gamescene.h"

#include <iostream>
#include <memory>
#include <string>
#include <tuple>
#include <vector>

char vertBuffer[4096];
char fragBuffer[4096];


GameScene::GameScene(){
    m_program = new QOpenGLShaderProgram();
}

void GameScene::initializeAtlas(GLuint* ptbo, const char* ppath){

    
}

void GameScene::initializeShaders(QOpenGLShader::ShaderType type, const char* path ){

    auto filename_shader = std::string(RESOURCES_DIR) + std::string{path};
    auto fileptr_shader = std::fopen(filename_shader.c_str(), "r");
    auto ptrCodeBuffer = (type == QOpenGLShader::Fragment) ? fragBuffer : vertBuffer;
    std::size_t bytesRead = std::fread(ptrCodeBuffer, 1, 4096, fileptr_shader);
    std::fclose(fileptr_shader);
    auto shaderSource = reinterpret_cast<char*>(ptrCodeBuffer); 

    if (m_program->addShaderFromSourceCode(type, shaderSource)){
    
        std::cout << "\n\tShader [OK]";
    
    } else {
        std::cout << "\n\t" << path << " Shader quite bad....." << std::endl;
        std::cout << "\n\tInfo: " <<  m_program->log().toStdString() << std::endl;
    }

}
void GameScene::bakeShader(){

    if (m_program->link()) std::cout << "\n\tProgram Linked [OK]" << std::endl;
    else {
        std::cout << "\n\tProgram linking quite bad....." << std::endl;
        std::cout << "\n\tInfo: " <<  m_program->log().toStdString() << std::endl;
    }

}
void GameScene::initializeGeometry(){

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

void GameScene::initialize(){

    if (!m_program) m_program = new QOpenGLShaderProgram(this);
    initializeGeometry();
    initializeShaders(QOpenGLShader::Vertex, "/shaders/level1.vert");
    initializeShaders(QOpenGLShader::Fragment, "/shaders/level1.frag");
    bakeShader();
    qimage = TextureManagerQT::initializeTexture(TextureManager::solvePath(ppath));


    
    m_matrixUniform = m_program->uniformLocation("matrix");
    m_p_selector = m_program->uniformLocation("spriteselector");

    m_cam.setCamera();

    installEventFilter(&m_im);
    connect(&m_im, &InputManager::escape, this, &GameScene::handleEscape);
    connect(&m_im, &InputManager::right_arrow, this, &GameScene::handleRight);
    connect(&m_im, &InputManager::left_arrow, this, &GameScene::handleLeft);

}

void GameScene::render(){

    Scene::render();

    m_program->bind();
    glBindVertexArray(m_vao);
    m_program->setUniformValue(m_matrixUniform, m_cam.getCamera());
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    m_program->release();

}


void GameScene::handleRight(){
    selector+=1;
    if (selector >= level1_data.sprites_entries) selector = 0;
    std::cout << "Selector: " << (int)selector << std::endl;
}
void GameScene::handleLeft(){
    selector -= 1;
    if (selector < 0) selector = level1_data.sprites_entries - 1;
    std::cout << "Selector: " << (int)selector << std::endl;
}

void GameScene::handleEscape(){
    std::cout << "Finishing Scene....." << std::endl;
    QCoreApplication::exit(0);
}
