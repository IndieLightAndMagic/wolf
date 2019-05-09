#include "introscene.h"
#include "texturemanager.h"


#include <tuple>
#include <memory>
#include <string>
#include <cassert>
#include <iostream>

#include <QDir>
#include <QScreen>
#include <QMatrix4x4>
#include <QElapsedTimer>
#include <QGuiApplication>
#include <QOpenGLShaderProgram>




HDC::IntroScene::IntroScene(){
    

}



void HDC::IntroScene::initializeGeometry(){

    m_soccer_court = new HDC::TexturedPlaneGeometry();

    m_soccer_court->setheight(0.3f);
    m_soccer_court->setwidth(0.3f);
    m_soccer_court->resetplane();


}
void HDC::IntroScene::processState(){

    float sliderValue{0.0f};

    m_elapsedTimeMeasurement = m_timer.elapsed();

    auto m_program = shaderProgram.get()[0]();    
    if (m_state == IntroState::START){

        m_state = IntroState::FADING_IN_CARNAGE;
        std::cout << "CARNAGE\n";
        m_timer.start();
        m_timeToExpire = 1000.0f;

        //As texture is going to be the same always, lets attach it.
        m_program->setUniformValue(m_textureUniform, 0);

    } else if (m_state == IntroState::FADING_IN_CARNAGE){

        float _timeFraction = m_elapsedTimeMeasurement / m_timeToExpire;
        _timeFraction = _timeFraction <= 1.0f ? _timeFraction : 1.0f;


        if (_timeFraction >= 1.0f) {
            std::cout << "STILL IN CARNAGE\n";
            m_state = IntroState::STILL_IN_CARNAGE;
            m_timer.start();
            m_timeToExpire = 3000.0f;
        }
        sliderValue = _timeFraction;

    } else if (m_state == IntroState::STILL_IN_CARNAGE){

        float _timeFraction = m_elapsedTimeMeasurement / m_timeToExpire;
        _timeFraction = _timeFraction < 1.0f ? _timeFraction : 1.0f;

        if (_timeFraction >= 1.0f) {
            std::cout << "FADING_OUT_CARNAGE\n";
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
            std::cout << "FADING IN CLASSIC\n";

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
        m_program->setUniformValue(m_textureUniform, m_soccer_court_texture);

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
    shaderProgram = std::make_shared<ShaderProgram>(
        (std::string(RESOURCES_DIR) + "/shaders/wolfy_intro.vert").c_str(),    
        (std::string(RESOURCES_DIR) + "/shaders/wolfy_intro.frag").c_str()
        );
    fastShaderProgram = shaderProgram.get()[0]();

    //Register Textures
    //Stage Textures
    auto [gltxture, bok] = HDC::TextureManager::registerimg(std::string{RESOURCES_DIR} + "/textures/soccerfieldgrass.png");
    assert(bok);
    auto slot_bok = HDC::TextureManager::getslot(gltxture);
    assert(std::get<1>(slot_bok));
    m_soccer_court_texture = std::get<0>(slot_bok);
    TextureManager::printtextureinformation(gltxture);


    auto m_program = shaderProgram.get()[0]();    

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

    Scene::render();
    fastShaderProgram->bind();
    m_soccer_court->enable();
    fastShaderProgram->setUniformValue(m_matrixUniform, m_cam.getCamera());
    processState();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    fastShaderProgram->release();

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
