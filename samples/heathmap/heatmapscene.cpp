#include "heatmapscene.h"

#include <tuple>
#include <memory>
#include <string>
#include <cassert>
#include <iostream>

#include <QDir>
#include <QImage>
#include <QScreen>
#include <QMatrix4x4>
#include <QElapsedTimer>
#include <QGuiApplication>
#include <QOpenGLShaderProgram>
#include <math.h>

static std::vector<unsigned int> ids {0,1,2,3,4,5,6,7,8,9,10,11,13,14,15,19,20,21,22,23,24,26,27,28,29,30,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57};
static unsigned int selectedidx = 0;
HDC::HeatmapRenderer::HeatmapRenderer(){

}
HDC::HeatmapRenderer::~HeatmapRenderer() {

}
void HDC::HeatmapRenderer::initializeGeometry(){

    m_soccer_court = new HDC::TexturedPlaneGeometry();
    m_soccer_court->setheight(0.55f);
    m_soccer_court->setwidth(1.0f);
    m_soccer_court->resetplane();


}
void HDC::HeatmapRenderer::initializeTextures(){

    //Register Textures
    //Stage Textures
    QImage* pqimg = new QImage(QString::fromStdString(std::string{RESOURCES_DIR} + "/textures/soccerfieldgrass.png"));
    m_soccer_court_texture  = new HDC::FastQTextureData(pqimg);

    HDC::Visitor v;
    v.Parse(std::string{RESOURCES_DIR} + "/json/court_cm.json");

    auto tdm = TrackletDataModel();
    tdm.getdata();
    tdm.normalizedata();
    tdm.getspeedandacceleration();

    m_heatmapplayer = new HDC::HeatMapPlayer(tdm);
    m_heatmapplayer->selecttrackletid(selectedidx);
    m_heatmapplayer->setperiod(30);
    m_heatmapplayer->start();


    //glBindTexture(GL_TEXTURE_2D, 0);
}
void HDC::HeatmapRenderer::initializeShader(){
    shaderProgram.reset();
    shaderProgram = std::make_shared<ShaderProgram>(
        (std::string(RESOURCES_DIR) + "/shaders/heathmap.vert").c_str(),
        (std::string(RESOURCES_DIR) + "/shaders/heathmap.frag").c_str()
        );
    fastShaderProgram = shaderProgram.get()[0]();

    m_matrixUniform        = fastShaderProgram->uniformLocation("matrix");
    m_court_textureUniform = fastShaderProgram->uniformLocation("court_texture");
    m_heat__textureUniform = fastShaderProgram->uniformLocation("heat__texture");
    m_blendSliderUniform   = fastShaderProgram->uniformLocation("fblend");
    m_fgridSliderUniform   = fastShaderProgram->uniformLocation("fgrid");

}

void HDC::HeatmapRenderer::initialize(){

    initializeOpenGLFunctions();

    initializeGeometry();
    initializeShader();
    initializeTextures();
    std::cout << "\n\tShaders [OK]" << std::endl;


    auto& mtx = m_cam.getCamera();
    mtx.rotate(-50.0f, QVector3D(1.0f, 0.0f, 0.0f));
    m_cam.setCameraPosition(0.0f, 0.0f, -2.0f);


}
void HDC::HeatmapRenderer::render(){

    QOpenGLFunctions *functions = QOpenGLContext::currentContext()->functions();

    m_soccer_court_texture->bind();
    m_heatmapplayer->updateTexture();
    m_heatmapplayer->bind();

    fastShaderProgram->bind();

    auto mtx = m_cam.getCamera();
    m_cam.setCameraPosition(0.0f, 0.0f, -5.0f);
    //auto rotationAxis = QVector3D{1.0f, 0.0f, 0.0f};
    //mtx.rotate(-50.0f, rotationAxis);

    fastShaderProgram->setUniformValue(m_matrixUniform, mtx);
    fastShaderProgram->setUniformValue(m_court_textureUniform, m_soccer_court_texture->gl.slot);
    fastShaderProgram->setUniformValue(m_heat__textureUniform, m_heatmapplayer->gl.slot);
    
    fastShaderProgram->setUniformValue(m_blendSliderUniform, m_fblend);

    m_soccer_court->enable();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    m_soccer_court->disable();

    fastShaderProgram->release();

}
