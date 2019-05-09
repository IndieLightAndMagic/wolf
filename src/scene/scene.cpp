#include "scene.h"

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


Scene::Scene(){
    
}


void Scene::initialize(){

}

void Scene::render(){


    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);
    glClear(GL_COLOR_BUFFER_BIT);

    
    ++m_frame;
}
