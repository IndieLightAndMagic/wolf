/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the documentation of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "openglwindow.h"

#include <iostream>
#include <memory>
#include <string>
#include <tuple>

#include <QtGui/QGuiApplication>
#include <QtGui/QMatrix4x4>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QScreen>
#include <QtCore/QDir>
#include <QtCore/qmath.h>
#include <QtCore/QElapsedTimer>

//! [1]
class TriangleWindow : public OpenGLWindow
{
public:

    enum class IntroState {
        START, 
        FADING_IN_CARNAGE, 
        STILL_IN_CARNAGE, 
        FADING_OUT_CARNAGE, 
        FADING_CLASSIC_IN, 
        STILL_IN_CLASSIC, 
        FADING_OUT_CLASSIC,
        IDLE 
    };

    std::shared_ptr<unsigned char> ptrVtxCodeBuffer{nullptr};
    std::shared_ptr<unsigned char> ptrFrgCodeBuffer{nullptr};
    QImage qimage{};
    
    TriangleWindow();

    void initialize() override;
    void render() override;

private:

    void processState();
    void initializeTextures(GLuint*, const char*);
    void initializeShaders();
    void initializeGeometry();

    GLuint m_posAttr;
    GLuint m_colAttr;
    GLuint m_texAttr;
    GLuint m_matrixUniform;
    GLuint m_textureUniform;
    GLuint m_pcsSliderUniform;
    GLuint m_vao, m_vbo, m_ebo;
    GLuint m_tbo[2];

    QOpenGLShaderProgram *m_program{nullptr};

    int m_frame{0};

    QElapsedTimer m_timer;
    uint64_t m_elapsedTimeMeasurement{0};

    TriangleWindow::IntroState m_state{IntroState::START};
    float m_timeToExpire{0.0f};
    unsigned int m_activeTextureIndex{0};
};

TriangleWindow::TriangleWindow(){

}
//! [1]

//! [2]
int main(int argc, char **argv){

    QGuiApplication app(argc, argv);

    QSurfaceFormat format;
    format.setSamples(16);

    TriangleWindow window;
    window.setFormat(format);
    window.resize(640, 480);
    window.show();

    window.setAnimating(true);

    return app.exec();
    
}




void TriangleWindow::initializeTextures(GLuint* ptbo, const char* ppath){

    auto filename_texture = std::string(RESOURCES_DIR) + ppath;
    auto testPath = QDir(QString(filename_texture.c_str()));
    auto absoluteTestPath = testPath.cleanPath(testPath.absoluteFilePath(filename_texture.c_str()));
    std::cout << "\n\tPath Test : " << absoluteTestPath.toStdString() << std::endl;
    qimage = QImage(absoluteTestPath).mirrored(false, true);
    auto [qimagewidth, qimageheight, qbpp] = std::make_tuple(qimage.width(), qimage.height(), qimage.pixelFormat().bitsPerPixel());
    std::cout << "Width :" << qimagewidth << std::endl << "Height: " << qimageheight << std::endl  << "Bitsperpixel: " << (unsigned long)qbpp << std::endl;
    auto colorformat = qimage.pixelFormat().typeInterpretation();
    if (colorformat  == QPixelFormat::UnsignedInteger ) std::cout << "Color is QPixelFormat::UnsignedInteger " << std::endl;     
    if (colorformat  == QPixelFormat::UnsignedShort ) std::cout << "Color is QPixelFormat::UnsignedShort " << std::endl;     
    if (colorformat  == QPixelFormat::UnsignedByte ) std::cout << "Color is QPixelFormat::UnsignedByte " << std::endl;     
    if (colorformat  == QPixelFormat::FloatingPoint ) std::cout << "Color is QPixelFormat::FloatingPoint " << std::endl;     

    auto colormodel = qimage.pixelFormat().colorModel();
    if (colormodel == QPixelFormat::RGB) std::cout << "Color model is QPixelFormat::RGB" << std::endl;   ;//0   The color model is RGB.
    if (colormodel == QPixelFormat::BGR) std::cout << "Color model is QPixelFormat::BGR" << std::endl;   ;//1   This is logically the opposite endian version of RGB. However, for ease of use it has its own model.
    if (colormodel == QPixelFormat::Indexed) std::cout << "Color model is QPixelFormat::Indexed" << std::endl;   ;//2   The color model uses a color palette.
    if (colormodel == QPixelFormat::Grayscale) std::cout << "Color model is QPixelFormat::Grayscale" << std::endl; ;//3   The color model is Grayscale.
    if (colormodel == QPixelFormat::CMYK) std::cout << "Color model is QPixelFormat::CMYK" << std::endl;  ;//4   The color model is CMYK.
    if (colormodel == QPixelFormat::HSL) std::cout << "Color model is QPixelFormat::HSL" << std::endl;   ;//5   The color model is HSL.
    if (colormodel == QPixelFormat::HSV) std::cout << "Color model is QPixelFormat::HSV" << std::endl;   ;//6   The color model is HSV.
    if (colormodel == QPixelFormat::YUV) std::cout << "Color model is QPixelFormat::YUV" << std::endl;   ;//7   The color model is YUV.
    if (colormodel == QPixelFormat::Alpha) std::cout << "Color model is QPixelFormat::Alpha" << std::endl; ;//8   There is no color model, only alpha is used.

    //Bind textures into opnegl.
    glGenTextures(1, ptbo);
    glBindTexture(GL_TEXTURE_2D, *ptbo); 
     // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, qimagewidth, qimageheight, 0, GL_BGRA, GL_UNSIGNED_BYTE, qimage.bits());
    glGenerateMipmap(GL_TEXTURE_2D);

}




void TriangleWindow::initializeShaders(){

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
void TriangleWindow::initializeGeometry(){

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
void TriangleWindow::processState(){
    
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
    
    } else {

        sliderValue = 1.0f;

    }
    m_program->setUniformValue(m_pcsSliderUniform, sliderValue);    

}
void TriangleWindow::initialize(){


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

}
//! [4]

//! [5]
void TriangleWindow::render(){


    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    glClear(GL_COLOR_BUFFER_BIT);

    m_program->bind();
    glBindVertexArray(m_vao);
    
    QMatrix4x4 matrix;
    matrix.perspective(60.0f, 4.0f/3.0f, 0.1f, 100.0f);
    matrix.translate(0.0f, 0.0f, -0.625f);
    matrix.rotate(0.0f * m_frame / screen()->refreshRate(), 0, 1, 0);
    
    m_program->setUniformValue(m_matrixUniform, matrix);
    

    processState();

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    m_program->release();

    ++m_frame;
}
//! [5]
