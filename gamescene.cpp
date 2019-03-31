#include "gamescene.h"

#include <iostream>
#include <memory>
#include <string>
#include <tuple>
#include <vector>

char vertBuffer[4096];
char fragBuffer[4096];
unsigned char atlas[] = {
  0x04, 0x02, 0x04, 0x00, /*Color of index 0 + 3755*/
  0x84, 0x86, 0x04, 0x00, /*Color of index 1 + 3755*/
  0x04, 0x02, 0x8c, 0x00, /*Color of index 2 + 3755*/
  0x44, 0x42, 0x04, 0x00, /*Color of index 3 + 3755*/
  0x04, 0x86, 0x84, 0x00, /*Color of index 4 + 3755*/
  0x04, 0xc6, 0xcc, 0x00, /*Color of index 5 + 3755*/
  0x8c, 0x02, 0x04, 0x00, /*Color of index 6 + 3755*/
  0x2c, 0x52, 0x84, 0x00, /*Color of index 7 + 3755*/
  0x04, 0x02, 0x4c, 0x00, /*Color of index 8 + 3755*/
  0x54, 0x82, 0xd4, 0x00, /*Color of index 9 + 3755*/
  0xfc, 0x42, 0x44, 0x00, /*Color of index 10 + 3755*/
  0xc4, 0xc2, 0xc4, 0x00, /*Color of index 11 + 3755*/
  0x04, 0x42, 0x44, 0x00, /*Color of index 12 + 3755*/
  0x44, 0x42, 0xfc, 0x00, /*Color of index 13 + 3755*/
  0x0c, 0x22, 0x2c, 0x00, /*Color of index 14 + 3755*/
  0x5c, 0xaa, 0xfc, 0x00, /*Color of index 15 + 3755*/
  0xd4, 0xd2, 0xd4, 0x00, /*Color of index 16 + 3755*/
  0x04, 0x02, 0xcc, 0x00, /*Color of index 17 + 3755*/
  0xcc, 0x02, 0x04, 0x00, /*Color of index 18 + 3755*/
  0x04, 0x6e, 0x74, 0x00, /*Color of index 19 + 3755*/
  0x9c, 0xfe, 0xfc, 0x00, /*Color of index 20 + 3755*/
  0xc4, 0xc2, 0x4c, 0x00, /*Color of index 21 + 3755*/
  0x3c, 0x66, 0xa4, 0x00, /*Color of index 22 + 3755*/
  0xb4, 0xb2, 0x24, 0x00, /*Color of index 23 + 3755*/
  0x64, 0x9e, 0xfc, 0x00, /*Color of index 24 + 3755*/
  0x44, 0x02, 0x04, 0x00, /*Color of index 25 + 3755*/
  0x6c, 0x6e, 0x04, 0x00, /*Color of index 26 + 3755*/
  0x8c, 0x8e, 0x8c, 0x00, /*Color of index 27 + 3755*/
  0x1c, 0x32, 0x44, 0x00, /*Color of index 28 + 3755*/
  0x24, 0x4a, 0x6c, 0x00, /*Color of index 29 + 3755*/
  0x04, 0x62, 0xcc, 0x00, /*Color of index 30 + 3755*/
  0x34, 0x32, 0x34, 0x00, /*Color of index 31 + 3755*/
  0x04, 0x02, 0xac, 0x00, /*Color of index 32 + 3755*/
  0x04, 0x56, 0xb4, 0x00, /*Color of index 33 + 3755*/
  0x24, 0x8a, 0xfc, 0x00, /*Color of index 34 + 3755*/
  0x94, 0xba, 0xfc, 0x00, /*Color of index 35 + 3755*/
  0x24, 0x22, 0xfc, 0x00, /*Color of index 36 + 3755*/
  0xfc, 0x26, 0x24, 0x00, /*Color of index 37 + 3755*/
  0xf4, 0xf6, 0xdc, 0x00, /*Color of index 38 + 3755*/
  0x64, 0x02, 0x04, 0x00, /*Color of index 39 + 3755*/
  0x9c, 0x9a, 0x04, 0x00, /*Color of index 40 + 3755*/
  0x04, 0xf6, 0xfc, 0x00, /*Color of index 41 + 3755*/
  0xb4, 0x02, 0x04, 0x00, /*Color of index 42 + 3755*/
  0x34, 0x5a, 0x8c, 0x00, /*Color of index 43 + 3755*/
  0x4c, 0x4a, 0x4c, 0x00, /*Color of index 44 + 3755*/
  0xa4, 0xc6, 0xfc, 0x00, /*Color of index 45 + 3755*/
  0x04, 0x02, 0xec, 0x00, /*Color of index 46 + 3755*/
  0xec, 0x02, 0x04, 0x00, /*Color of index 47 + 3755*/
  0x7c, 0x7a, 0x04, 0x00, /*Color of index 48 + 3755*/
  0x4c, 0x7e, 0xcc, 0x00, /*Color of index 49 + 3755*/
  0x04, 0x02, 0x74, 0x00, /*Color of index 50 + 3755*/
  0x14, 0x2e, 0x3c, 0x00, /*Color of index 51 + 3755*/
  0x64, 0x66, 0x64, 0x00, /*Color of index 52 + 3755*/
  0x44, 0x72, 0xb4, 0x00, /*Color of index 53 + 3755*/
  0xac, 0xaa, 0xac, 0x00, /*Color of index 54 + 3755*/
  0x5c, 0x8e, 0xec, 0x00, /*Color of index 55 + 3755*/
  0xdc, 0xfe, 0xfc, 0x00, /*Color of index 56 + 3755*/
  0x04, 0x02, 0x9c, 0x00, /*Color of index 57 + 3755*/
  0x04, 0x9e, 0x9c, 0x00, /*Color of index 58 + 3755*/
  0x9c, 0x02, 0x04, 0x00, /*Color of index 59 + 3755*/
  0xdc, 0xde, 0x9c, 0x00, /*Color of index 60 + 3755*/
  0x04, 0x56, 0x5c, 0x00, /*Color of index 61 + 3755*/
  0x2c, 0x2e, 0x2c, 0x00, /*Color of index 62 + 3755*/
  0x74, 0xa6, 0xfc, 0x00, /*Color of index 63 + 3755*/
  0x04, 0x02, 0xe4, 0x00, /*Color of index 64 + 3755*/
  0xe4, 0x02, 0x04, 0x00, /*Color of index 65 + 3755*/
  0xcc, 0xce, 0x04, 0x00, /*Color of index 66 + 3755*/
  0x5c, 0x02, 0x04, 0x00, /*Color of index 67 + 3755*/
  0x74, 0x76, 0x04, 0x00, /*Color of index 68 + 3755*/
  0x1c, 0x3a, 0x4c, 0x00, /*Color of index 69 + 3755*/
  0x04, 0x7a, 0xfc, 0x00, /*Color of index 70 + 3755*/
  0x3c, 0x3a, 0x3c, 0x00, /*Color of index 71 + 3755*/
  0x04, 0x02, 0xbc, 0x00, /*Color of index 72 + 3755*/
  0xbc, 0xba, 0xfc, 0x00, /*Color of index 73 + 3755*/
  0x74, 0x02, 0x04, 0x00, /*Color of index 74 + 3755*/
  0xa4, 0xa6, 0x04, 0x00, /*Color of index 75 + 3755*/
  0x5c, 0xfa, 0xfc, 0x00, /*Color of index 76 + 3755*/
  0x3c, 0x62, 0x9c, 0x00, /*Color of index 77 + 3755*/
  0xbc, 0xd6, 0xfc, 0x00, /*Color of index 78 + 3755*/
  0x7c, 0x7e, 0x7c, 0x00, /*Color of index 79 + 3755*/
  0x44, 0x9a, 0xfc, 0x00, /*Color of index 80 + 3755*/
  0x8c, 0x8e, 0x04, 0x00, /*Color of index 81 + 3755*/
  0x5c, 0x5a, 0x04, 0x00, /*Color of index 82 + 3755*/
  0x04, 0xda, 0xe4, 0x00, /*Color of index 83 + 3755*/
  0x04, 0x4e, 0x9c, 0x00, /*Color of index 84 + 3755*/
  0x04, 0x02, 0x64, 0x00, /*Color of index 85 + 3755*/
  0x54, 0x8a, 0xdc, 0x00, /*Color of index 86 + 3755*/
  0x24, 0x42, 0x5c, 0x00, /*Color of index 87 + 3755*/
  0x5c, 0x5e, 0xfc, 0x00, /*Color of index 88 + 3755*/
  0x24, 0x22, 0x24, 0x00, /*Color of index 89 + 3755*/
  0xdc, 0xde, 0xdc, 0x00, /*Color of index 90 + 3755*/
  0x04, 0x02, 0xd4, 0x00, /*Color of index 91 + 3755*/
  0xd4, 0x02, 0x04, 0x00, /*Color of index 92 + 3755*/
  0xbc, 0xfe, 0xfc, 0x00, /*Color of index 93 + 3755*/
  0xcc, 0xca, 0x74, 0x00, /*Color of index 94 + 3755*/
  0x44, 0x6a, 0xac, 0x00, /*Color of index 95 + 3755*/
  0xb4, 0xb6, 0x24, 0x00, /*Color of index 96 + 3755*/
  0x9c, 0x9e, 0xfc, 0x00, /*Color of index 97 + 3755*/
  0x4c, 0x02, 0x04, 0x00, /*Color of index 98 + 3755*/
  0x74, 0x72, 0x04, 0x00, /*Color of index 99 + 3755*/
  0x9c, 0x9a, 0x9c, 0x00, /*Color of index 100 + 3755*/
  0x2c, 0x4e, 0x74, 0x00, /*Color of index 101 + 3755*/
  0x04, 0x6e, 0xe4, 0x00, /*Color of index 102 + 3755*/
  0x34, 0x36, 0x34, 0x00, /*Color of index 103 + 3755*/
  0x04, 0x02, 0xb4, 0x00, /*Color of index 104 + 3755*/
  0x9c, 0xbe, 0xfc, 0x00, /*Color of index 105 + 3755*/
  0xec, 0xee, 0xec, 0x00, /*Color of index 106 + 3755*/
  0x9c, 0x9e, 0x04, 0x00, /*Color of index 107 + 3755*/
  0x24, 0xf6, 0xfc, 0x00, /*Color of index 108 + 3755*/
  0xbc, 0x02, 0x04, 0x00, /*Color of index 109 + 3755*/
  0x34, 0x5e, 0x94, 0x00, /*Color of index 110 + 3755*/
  0x54, 0x56, 0x54, 0x00, /*Color of index 111 + 3755*/
  0x04, 0x02, 0xfc, 0x00, /*Color of index 112 + 3755*/
  0xfc, 0x02, 0x04, 0x00, /*Color of index 113 + 3755*/
  0x7c, 0x7e, 0x04, 0x00, /*Color of index 114 + 3755*/
  0x7c, 0x7e, 0xfc, 0x00, /*Color of index 115 + 3755*/
  0x04, 0x02, 0x7c, 0x00, /*Color of index 116 + 3755*/
  0x74, 0x72, 0x74, 0x00, /*Color of index 117 + 3755*/
  0x4c, 0x7a, 0xbc, 0x00, /*Color of index 118 + 3755*/
  0xb4, 0xb6, 0xb4, 0x00, /*Color of index 119 + 3755*/
  0xfc, 0xfe, 0xfc, 0x00, /*Color of index 120 + 3755*/
  0x04, 0x02, 0xa4, 0x00, /*Color of index 121 + 3755*/
  0x04, 0xae, 0xb4, 0x00, /*Color of index 122 + 3755*/
  0xa4, 0x02, 0x04, 0x00, /*Color of index 123 + 3755*/
  0xec, 0xea, 0xbc, 0x00, /*Color of index 124 + 3755*/
  0x84, 0xb2, 0xfc, 0x00, /*Color of index 125 + 3755*/
  0x1c, 0x3e, 0x54, 0x00, /*Color of index 126 + 3755*/
  0x7c, 0x02, 0x04, 0x00, /*Color of index 127 + 3755*/
  0xdc, 0xda, 0xfc, 0x00, /*Color of index 128 + 3755*/
  0x5c, 0x96, 0xf4, 0x00 /*Color of index 129..... SIZE 45580  + 3755*/
         
  
};

GameScene::GameScene(){
    m_atlas_data = atlas;
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
    initializeShaders(QOpenGLShader::Vertex, "/shaders/level1.vert");
    initializeShaders(QOpenGLShader::Fragment, "/shaders/level1.frag");
    bakeShader();

    initializeGeometry();

    m_matrixUniform = m_program->uniformLocation("matrix");
    m_p_selector = m_program->uniformLocation("selector");

    /*auto shaderid = m_program->programId();
    unsigned int uniformBlockIndex = glGetUniformBlockIndex(shaderid, "TUMADREENBOLA");
    glUniformBlockBinding(shaderid, uniformBlockIndex, 0);*/

    glGenBuffers(1, &m_ubo);
    glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(unsigned char)*520, nullptr, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);    

    // define the range of the buffer that links to a uniform binding point
    glBindBufferRange(GL_UNIFORM_BUFFER, 0, m_ubo, 0, sizeof(unsigned char)*520);


    glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(unsigned char)*520, (unsigned char*)atlas);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    
    m_valid = true;
    std::cout << "\n\tShaders [OK]" << std::endl; 

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
    m_program->setUniformValue(m_p_selector, selector);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    m_program->release();

}


void GameScene::handleRight(){
    selector+=1;
    if (selector > 33) selector = 0;
    std::cout << "Selector: " << (int)selector << std::endl;
}
void GameScene::handleLeft(){
    selector -= 1;
    if (selector < 0) selector = 32;
    std::cout << "Selector: " << (int)selector << std::endl;
}

void GameScene::handleEscape(){
    std::cout << "Finishing Scene....." << std::endl;
    QCoreApplication::exit(0);
}
