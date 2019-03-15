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

void IntroScene::initializeTextures(GLuint* ptbo, const char* ppath){

    qimage = TextureManagerQT::initializeTexture(ptbo, TextureManager::solvePath(ppath));
    auto filename_atlas = std::string(RESOURCES_DIR) + "/atlases/walls.at.json";
    auto filename_textures = std::string(RESOURCES_DIR) + "/atlases/walls.json";
    auto atlas = TextureAtlas(filename_textures, filename_atlas);
}

void IntroScene::initializeShaders(){


    auto filename_vertex_shader = std::string(RESOURCES_DIR) + "/shaders/wolfy_intro.vert";
    auto filename_fragment_shader = std::string(RESOURCES_DIR) + "/shaders/wolfy_intro.frag";
    auto fileptr_vertex_shader = std::fopen(filename_vertex_shader.c_str(), "r");
    auto fileptr_vertex_shader_ok = std::string( fileptr_vertex_shader != nullptr ? "[OK]" : "[FAILED]");  
    auto fileptr_fragment_shader = std::fopen(filename_fragment_shader.c_str(), "r");
    auto fileptr_fragment_shader_ok = std::string(fileptr_fragment_shader != nullptr ? "[OK]" : "[FAILED]");  

    std::cout <<"\n\tWolfy Vert: " << filename_vertex_shader << " " << fileptr_vertex_shader_ok << std::endl;
    std::cout <<"\n\tWolfy Frag: " << filename_fragment_shader << " " << fileptr_fragment_shader_ok << std::endl;

    if (fileptr_vertex_shader == nullptr || fileptr_fragment_shader == nullptr) return;

    std::fseek(fileptr_vertex_shader, 0, SEEK_END);
    std::size_t vtxShaderFileSize = std::ftell(fileptr_vertex_shader);
    std::fseek(fileptr_vertex_shader, 0, SEEK_SET);
    
    std::fseek(fileptr_fragment_shader, 0, SEEK_END);
    std::size_t frgShaderFileSize = std::ftell(fileptr_fragment_shader);
    std::fseek(fileptr_fragment_shader, 0, SEEK_SET);

    std::cout << "\n\tWolfey Vert Size : " << vtxShaderFileSize << "\n\tWolfey Frag Size : " << frgShaderFileSize << std::endl;

    ptrVtxCodeBuffer = std::shared_ptr<unsigned char>(new unsigned char[vtxShaderFileSize], std::default_delete<unsigned char[]>());
    ptrFrgCodeBuffer = std::shared_ptr<unsigned char>(new unsigned char[frgShaderFileSize], std::default_delete<unsigned char[]>());
        
    if (ptrVtxCodeBuffer == nullptr || ptrFrgCodeBuffer == nullptr) return;

    std::size_t vtxBytesRead = std::fread(ptrVtxCodeBuffer.get(), 1, vtxShaderFileSize, fileptr_vertex_shader);
    std::size_t frgBytesRead = std::fread(ptrFrgCodeBuffer.get(), 1, frgShaderFileSize, fileptr_fragment_shader);

    if (vtxBytesRead != vtxShaderFileSize)
        std::cout << "Warning :\n\tBytes read from vertex shader file : " << vtxBytesRead << "\n\tshader file size : " << vtxShaderFileSize << std::endl; 

    if (frgBytesRead != frgShaderFileSize)
        std::cout << "Warning :\n\tBytes read from vertex shader file : " << frgBytesRead << "\n\tshader file size : " << frgShaderFileSize << std::endl; 

    std::fclose(fileptr_vertex_shader);
    std::fclose(fileptr_fragment_shader);

    std::cout << "Wolfey vertex shader :" << std::endl;
    for (std::size_t index = 0; index < vtxBytesRead; ++index){
        std::cout << ptrVtxCodeBuffer.get()[index];
        if ( (index + 1) == vtxShaderFileSize ){
            std::cout << std::endl;
        }
    }

    std::cout << "Wolfey fragment shader :" << std::endl;
    for (std::size_t index = 0; index < frgBytesRead; ++index){
        std::cout << ptrFrgCodeBuffer.get()[index];
        if ( (index + 1) == frgShaderFileSize ){
            std::cout << std::endl;
        }
    }

    auto vertexShaderSource = reinterpret_cast<char*>(ptrVtxCodeBuffer.get()); 
    auto fragmentShaderSource = reinterpret_cast<char*>(ptrFrgCodeBuffer.get()); 

    m_program = new QOpenGLShaderProgram(this);
    if (m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource)) std::cout << "\n\tVertex Shader [OK]";
    else {
        std::cout << "\n\tVertex Shader quite bad....." << std::endl;
        std::cout << "\n\tInfo: " <<  m_program->log().toStdString() << std::endl;
    }
    if (m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource)) std::cout << "\n\tVertex Shader [OK]";
    else {
        std::cout << "\n\tFragment Shader quite bad....." << std::endl;
        std::cout << "\n\tInfo: " <<  m_program->log().toStdString() << std::endl;
    }
    if (m_program->link()) std::cout << "\n\tProgram Linked [OK]" << std::endl;
    else {
        std::cout << "\n\tProgram linking quite bad....." << std::endl;
        std::cout << "\n\tInfo: " <<  m_program->log().toStdString() << std::endl;
    }

}
void IntroScene::initializeGeometry(){

    float vertices[] = {
        // positions          // colors           // texture coords
         0.5000f,  0.3125f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         0.5000f, -0.3125f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5000f, -0.3125f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5000f,  0.3125f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
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
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


}
void IntroScene::processState(){
    
    float sliderValue{0.0f};

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_tbo[0]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_tbo[1]);
    
    
    m_elapsedTimeMeasurement = m_timer.elapsed();

    
    if (m_state == IntroState::START){

        m_state = IntroState::FADING_IN_CARNAGE;
        m_timer.start();
        m_timeToExpire = 1000.0f;
        
        //As texture is going to be the same always, lets attach it.
        m_program->setUniformValue(m_textureUniform, 0);

    } else if (m_state == IntroState::FADING_IN_CARNAGE){

        float _timeFraction = m_elapsedTimeMeasurement / m_timeToExpire;
        _timeFraction = _timeFraction <= 1.0f ? _timeFraction : 1.0f;


        if (_timeFraction >= 1.0f) {
            m_state = IntroState::STILL_IN_CARNAGE;
            m_timer.start();
            m_timeToExpire = 3000.0f;
        }
        sliderValue = _timeFraction;
    
    } else if (m_state == IntroState::STILL_IN_CARNAGE){

        float _timeFraction = m_elapsedTimeMeasurement / m_timeToExpire;
        _timeFraction = _timeFraction < 1.0f ? _timeFraction : 1.0f;

        if (_timeFraction >= 1.0f) {
            m_state = IntroState::FADING_OUT_CARNAGE;
            m_timer.start();
            m_timeToExpire = 1000.0f;
        }
        sliderValue = 1.0f;
        

    } else if (m_state == IntroState::FADING_OUT_CARNAGE){

        float _timeFraction = m_elapsedTimeMeasurement / m_timeToExpire;
        _timeFraction = 1.0 - _timeFraction;
        _timeFraction = _timeFraction >= 0.0f ? _timeFraction : 0.0f;

        if (_timeFraction <= 0.0f) {
            m_state = IntroState::FADING_CLASSIC_IN;
            m_timer.start();
            m_timeToExpire = 1000.0f;
        }
        sliderValue = _timeFraction;

    } else if (m_state == IntroState::FADING_CLASSIC_IN){

        float _timeFraction = m_elapsedTimeMeasurement / m_timeToExpire;
        _timeFraction = _timeFraction <= 1.0f ? _timeFraction : 1.0f;

        if (_timeFraction >= 1.0f) {
            m_state = IntroState::IDLE;
            m_timer.start();
            m_timeToExpire = 3000.0f;
        }
        sliderValue = _timeFraction;

        //As texture is going to be the same always, lets attach it.
        m_program->setUniformValue(m_textureUniform, 1);
    
    } else if(m_state == IntroState::FINISH){

        QGuiApplication::exit();

    } else {

        sliderValue = 1.0f;

    }
    m_program->setUniformValue(m_pcsSliderUniform, sliderValue);    

}
void IntroScene::initialize(){


    std::cout <<"Wolfy resources:" << std::endl;
    
    initializeGeometry();
    initializeShaders();
    initializeTextures(&m_tbo[0], "/textures/pgrate.png");
    initializeTextures(&m_tbo[1], "/textures/classic.png");


    
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
