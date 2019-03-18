#include "introscene.h"
#include "texturemanager.h"
#include <iostream>
#include <memory>
#include <string>
#include <tuple>

#include <QtCore/QDir>
#include <QtGui/QScreen>
#include <QtGui/QMatrix4x4>
#include <QtCore/QElapsedTimer>
#include <QtGui/QGuiApplication>
#include <QtGui/QOpenGLShaderProgram>


IntroScene::IntroScene(){
    
}

void IntroScene::initializeTextureAtlas(GLuint* ptbo, const char* ppath){

    auto filename_atlas = std::string(RESOURCES_DIR) + "/atlases/walls.at.json";
    auto filename_textures = std::string(RESOURCES_DIR) + "/atlases/walls.png";
    auto m_atlas = TextureAtlas(filename_textures, filename_atlas);
}

void IntroScene::initializeShaders(){

    auto filename_shader = std::string(RESOURCES_DIR) + "/shaders/someshader";
    auto fileptr_shader = std::fopen(filename_shader.c_str(), "r");
    auto fileptr_shader_ok = std::string( fileptr_shader != nullptr ? "[OK]" : "[FAILED]");  
    
    std::cout <<"\n\tWolfy Shader: " << filename_shader << " " << fileptr_shader_ok << std::endl;
    
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

    auto vertexShaderSource = reinterpret_cast<char*>(ptrVtxCodeBuffer.get()); 

    m_program = new QOpenGLShaderProgram(this);
    /*if (m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource)) std::cout << "\n\tShader [OK]";
    else {
        std::cout << "\n\tShader quite bad....." << std::endl;
        std::cout << "\n\tInfo: " <<  m_program->log().toStdString() << std::endl;
    }
    if (m_program->link()) std::cout << "\n\tProgram Linked [OK]" << std::endl;
    else {
        std::cout << "\n\tProgram linking quite bad....." << std::endl;
        std::cout << "\n\tInfo: " <<  m_program->log().toStdString() << std::endl;
    }*/

}

void IntroScene::initializeGeometry(){

    float vertices[] = {
        // positions                // colors           
         0.5000f,  0.3125f, 0.0f,   1.0f, 0.0f, 0.0f,   // top right
         0.5000f, -0.3125f, 0.0f,   0.0f, 1.0f, 0.0f,   // bottom right
        -0.5000f, -0.3125f, 0.0f,   0.0f, 0.0f, 1.0f,   // bottom left
        -0.5000f,  0.3125f, 0.0f,   1.0f, 1.0f, 0.0f    // top left 
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);    

}

void IntroScene::initialize(){


    std::cout <<"Wolfy resources:" << std::endl;
    
    initializeShaders();
    initializeTextureAtlases(&m_tbo[1], "/textures/classic.png");

    m_posAttr = m_program->attributeLocation("posAttr");
    m_colAttr = m_program->attributeLocation("colAttr");
    m_texAttr = m_program->attributeLocation("texAttr");
    m_matrixUniform = m_program->uniformLocation("matrix");
    m_textureUniform = m_program->uniformLocation("ourTexture");
    m_pcsSliderUniform = m_program->uniformLocation("pcsSlider");


    m_valid = true;
    std::cout << "\n\tShaders [OK]" << std::endl; 


    m_cam.setCamera();


    installEventFilter(&m_im);
    connect(&m_im, &InputManager::escape,
            this, &IntroScene::handleEscape);
    connect(&m_im, &InputManager::up_arrow,
            this, &IntroScene::handleUp);
    connect(&m_im, &InputManager::down_arrow,
            this, &IntroScene::handleDown);

}

void IntroScene::render(){

    Scene::render();

    m_program->bind();
    glBindVertexArray(m_vao);
    m_program->setUniformValue(m_matrixUniform, m_cam.getCamera());
    processState();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    m_program->release();

}
void IntroScene::handleEscape(){
    std::cout << "Finishing Scene....." << std::endl;
    m_state = IntroState::FINISH;
}
void IntroScene::handleUp(){
    m_cam.setCameraPositionDelta(0.0f, 0.0f, 0.1f);
}
void IntroScene::handleDown(){
    m_cam.setCameraPositionDelta(0.0f, 0.0f, -0.1f);
}
