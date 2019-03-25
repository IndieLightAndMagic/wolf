#include "gamescene.h"
#include "texturemanager.h"
#include <iostream>
#include <memory>
#include <string>
#include <tuple>

#include <QtCore/QDir>
#include <QtGui/QScreen>
#include <QtGui/QMatrix4x4>
#include <QtGui/QOpenGLShader>
#include <QtCore/QElapsedTimer>
#include <QtGui/QGuiApplication>
#include <QtGui/QOpenGLShaderProgram>


GameScene::GameScene(){
    
}
void GameScene::initializeShaders(QOpenGLShader::ShaderType type, const char* path ){

    auto filename_shader = std::string(RESOURCES_DIR) + std::string{path};
    auto fileptr_shader = std::fopen(filename_shader.c_str(), "r");
    auto fileptr_shader_ok = std::string( fileptr_shader != nullptr ? "[OK]" : "[FAILED]");  
    
    std::cout << "\n\tWolfy Shader: " << filename_shader << " " << fileptr_shader_ok << std::endl;
    
    if (fileptr_shader == nullptr) return;

    std::fseek(fileptr_shader, 0, SEEK_END);
    std::size_t shaderFileSize = std::ftell(fileptr_shader);
    std::fseek(fileptr_shader, 0, SEEK_SET);
    
    std::cout << "\n\tWolfey Size : " << shaderFileSize << std::endl;

    ptrCodeBuffer = std::shared_ptr<unsigned char>(new unsigned char[shaderFileSize], std::default_delete<unsigned char[]>());
        
    if (ptrCodeBuffer == nullptr) return;

    std::size_t bytesRead = std::fread(ptrCodeBuffer.get(), 1, shaderFileSize, fileptr_shader);
    
    if (bytesRead != shaderFileSize)
        std::cout << "Warning :\n\tBytes read from shader file : " << bytesRead << "\n\tshader file size : " << shaderFileSize << std::endl; 

    std::fclose(fileptr_shader);

    std::cout << "Wolfey shader :" << std::endl;
    for (std::size_t index = 0; index < bytesRead; ++index){
        std::cout << ptrCodeBuffer.get()[index];
        if ( (index + 1) == shaderFileSize ){
            std::cout << std::endl;
        }
    }

    auto shaderSource = reinterpret_cast<char*>(ptrCodeBuffer.get()); 

    if (!m_program) m_program = new QOpenGLShaderProgram(this);

    if (m_program->addShaderFromSourceCode(type, shaderSource)){
    
        std::cout << "\n\tShader [OK]";
        if (type == QOpenGLShader::Fragment){
            if (m_program->link()) std::cout << "\n\tProgram Linked [OK]" << std::endl;
            else {
                std::cout << "\n\tProgram linking quite bad....." << std::endl;
                std::cout << "\n\tInfo: " <<  m_program->log().toStdString() << std::endl;
            }
        }
    
    } else {
        std::cout << "\n\t" << path << " Shader quite bad....." << std::endl;
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

    initializeGeometry();
    initializeShaders(QOpenGLShader::Vertex, "/shaders/level1.vert");
    initializeShaders(QOpenGLShader::Fragment, "/shaders/level1.frag");

    m_posAttr = m_program->attributeLocation("posAttr");
    m_colAttr = m_program->attributeLocation("colAttr");
    m_texAttr = m_program->attributeLocation("texAttr");
    m_matrixUniform = m_program->uniformLocation("matrix");
    
    m_valid = true;
    std::cout << "\n\tShaders [OK]" << std::endl; 

    m_cam.setCamera();

    installEventFilter(&m_im);
    connect(&m_im, &InputManager::escape, this, &GameScene::handleEscape);

}

void GameScene::render(){

    Scene::render();

    m_program->bind();
    glBindVertexArray(m_vao);
    m_program->setUniformValue(m_matrixUniform, m_cam.getCamera());
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    m_program->release();

}
void GameScene::handleEscape(){
    std::cout << "Finishing Scene....." << std::endl;
    QCoreApplication::exit(0);
}
