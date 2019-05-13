#include "heatmapscene.h"

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
#include <math.h>



HDC::HeatMapScene::HeatMapScene(){

}

void HDC::HeatMapScene::initializeGeometry(){

    m_soccer_court = new HDC::TexturedPlaneGeometry();
    m_soccer_court->setheight(0.55f);
    m_soccer_court->setwidth(1.0f);
    m_soccer_court->resetplane();


}
void HDC::HeatMapScene::initializeTextures(){

    //Register Textures
    //Stage Textures
    m_soccer_court_texture  = HDC::TextureManager::registerimg(std::string{RESOURCES_DIR} + "/textures/soccerfieldgrass.png");

    m_heatmap_texture       = HDC::TextureManager::registerimg("heatmap",
        m_soccer_court_texture->width,
        m_soccer_court_texture->height,
        m_soccer_court_texture->format_info_vendor
        );

    auto size = m_soccer_court_texture->width * m_soccer_court_texture->height;
    for ( auto index = 0; index < size; ++index){
                
        m_heatmap_texture->data[index * 4 + (index % 4)] = 0xFF;

    }
    m_heatmap_texture->updateTexture();
    //glBindTexture(GL_TEXTURE_2D, 0);
}

void HDC::HeatMapScene::initialize(){

    initializeGeometry();
    shaderProgram = std::make_shared<ShaderProgram>(
        (std::string(RESOURCES_DIR) + "/shaders/heathmap.vert").c_str(),
        (std::string(RESOURCES_DIR) + "/shaders/heathmap.frag").c_str()
        );
    fastShaderProgram = shaderProgram.get()[0]();

    initializeTextures();

    auto m_program = shaderProgram.get()[0]();    

    m_matrixUniform = m_program->uniformLocation("matrix");
    m_court_textureUniform = m_program->uniformLocation("court_texture");
    m_heat__textureUniform = m_program->uniformLocation("heat__texture");
    m_blendSliderUniform = m_program->uniformLocation("fblend");
    m_fgridSliderUniform = m_program->uniformLocation("fgrid");

    m_valid = true;
    std::cout << "\n\tShaders [OK]" << std::endl; 

    m_cam.setCamera();

    installEventFilter(&m_im);

    connect(&m_im, &InputManager::escape, this, &HDC::HeatMapScene::handleEscape);
    connect(&m_im, &InputManager::up_arrow, this, &HDC::HeatMapScene::handleUp);
    connect(&m_im, &InputManager::down_arrow, this, &HDC::HeatMapScene::handleDown);
    connect(&m_im, &InputManager::m_wheel, this, &HDC::HeatMapScene::handleWheel);
    connect(&m_im, &InputManager::m_wheelreleased, this, &HDC::HeatMapScene::handleWheelButton);

    tp.setperiod(250);
    tp.opentrackfile("/json/court_cm.json");
    tp.start();

}

void HDC::HeatMapScene::render(){

    Scene::render();

    m_soccer_court->enable();
    m_soccer_court_texture->bind();
    m_heatmap_texture->bind();

    fastShaderProgram->bind();
    fastShaderProgram->setUniformValue(m_matrixUniform, m_cam.getCamera());
    fastShaderProgram->setUniformValue(m_court_textureUniform, m_soccer_court_texture->gl.slot);
    fastShaderProgram->setUniformValue(m_heat__textureUniform, m_heatmap_texture->gl.slot);
    
    fastShaderProgram->setUniformValue(m_fgridSliderUniform, m_fgrid);
    fastShaderProgram->setUniformValue(m_blendSliderUniform, m_fblend);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    fastShaderProgram->release();

}
void HDC::HeatMapScene::handleEscape(){
    std::cout << "Finishing Scene....." << std::endl;
    m_state = IntroState::FINISH;
    QGuiApplication::exit();
}
void HDC::HeatMapScene::handleUp(){
    m_cam.setCameraPositionDelta(0.0f, 0.0f, 0.1f);

}
void HDC::HeatMapScene::handleDown(){
    m_cam.setCameraPositionDelta(0.0f, 0.0f, -0.1f);
}

void HDC::HeatMapScene::handleWheel(int delta){

    if (m_wheelstate == WheelState::GRID){

        if (grid_exponent == 10 && delta > 0) return;
        if (!grid_exponent && delta < 0) return;

        grid_exponent += delta;
        grid_exponent = grid_exponent % 11 ;
        m_fgrid = powf(2,grid_exponent);


    } else {
        auto fdelta = static_cast<float>(delta);
        fdelta /= 10.0f;
        m_fblend += fdelta;
        if (m_fblend < 0.0f) m_fblend = 0.0f;
        else if (m_fblend > 1.0f) m_fblend = 1.0f;
    }



}
void HDC::HeatMapScene::handleWheelButton(){
    m_wheelstate = m_wheelstate == WheelState::GRID ? WheelState::BLEND : WheelState::GRID;
    auto message = m_wheelstate == WheelState::GRID ? std::string{"GRID mode..."} : std::string{"BLEND mode..."};
    std::cout << message << std::endl;
}
