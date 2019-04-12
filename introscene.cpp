#include "introscene.h"
#include "texturemanager.h"
#include <iostream>
#include <memory>
#include <string>
#include <tuple>

#include <QDir>
#include <QScreen>
#include <QMatrix4x4>
#include <QElapsedTimer>
#include <QGuiApplication>
#include <QOpenGLShaderProgram>


HDC::IntroScene::IntroScene(){
    
}

void HDC::IntroScene::initializeTextures(GLuint* ptbo, const char* ppath){

    qimage = TextureManagerQT::initializeTexture(TextureManager::solvePath(ppath));
    auto filename_atlas = std::string(RESOURCES_DIR) + "/atlases/walls.at.json";
    auto filename_textures = std::string(RESOURCES_DIR) + "/atlases/walls.json";
    auto atlas = TextureAtlas(filename_textures, filename_atlas);
}

void HDC::IntroScene::initializeGeometry(){

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
void HDC::IntroScene::processState(){
    
    float sliderValue{0.0f};

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_tbo[0]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_tbo[1]);
    
    
    m_elapsedTimeMeasurement = m_timer.elapsed();

    auto m_program = shaderProgram.GetProgram();    
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
void HDC::IntroScene::initialize(){


    std::cout <<"Wolfy resources:" << std::endl;
    
    initializeGeometry();
    
    shaderProgram.AddShader(ShaderProgram::ShaderType::VTX, (std::string(RESOURCES_DIR) + "/shaders/wolfy_intro.vert").c_str());
    shaderProgram.AddShader(ShaderProgram::ShaderType::FRG, (std::string(RESOURCES_DIR) + "/shaders/wolfy_intro.frag").c_str());
    
    initializeTextures(&m_tbo[0], "/textures/pgrate.png");
    initializeTextures(&m_tbo[1], "/textures/classic.png");


    
    auto m_program = shaderProgram.GetProgram();    
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
            this, &HDC::IntroScene::handleEscape);
    connect(&m_im, &InputManager::up_arrow,
            this, &HDC::IntroScene::handleUp);
    connect(&m_im, &InputManager::down_arrow,
            this, &HDC::IntroScene::handleDown);

}

void HDC::IntroScene::render(){

    auto m_program = shaderProgram.GetProgram();    
    Scene::render();
    m_program->bind();
    glBindVertexArray(m_vao);
    m_program->setUniformValue(m_matrixUniform, m_cam.getCamera());
    processState();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    m_program->release();

}
void HDC::IntroScene::handleEscape(){
    std::cout << "Finishing Scene....." << std::endl;
    m_state = IntroState::FINISH;
}
void HDC::IntroScene::handleUp(){
    m_cam.setCameraPositionDelta(0.0f, 0.0f, 0.1f);
}
void HDC::IntroScene::handleDown(){
    m_cam.setCameraPositionDelta(0.0f, 0.0f, -0.1f);
}
