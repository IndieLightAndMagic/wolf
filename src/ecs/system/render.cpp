#include "render.h"

#include <QDebug>
#include <QPainter>
#include <QKeyEvent>
#include <QPaintEngine>
#include <qmath.h>


ECS_SYSTEM::Renderer::Renderer(QObject* parent):QObject(parent)
{

    m_ptimer = new QElapsedTimer();
    m_ptimer->start();

}

ECS_SYSTEM::Renderer::~Renderer()
{
    delete m_ptimer;
}

void ECS_SYSTEM::Renderer::initialize()
{

    initializeOpenGLFunctions();
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    
    /*program1.addCacheableShaderFromSourceFile(QOpenGLShader::Vertex, QString::fromStdString(std::string{RESOURCES_DIR} + "/shaders/heatmap_t.vert"));
    program1.addCacheableShaderFromSourceFile(QOpenGLShader::Fragment, QString::fromStdString(std::string{RESOURCES_DIR} + "/shaders/heatmap_t.frag"));
    program1.link();

    createGeometry();
    
    
    matrixUniform1 = program1.uniformLocation("matrix");
    courtUniform   = program1.uniformLocation("court_texture");

    m_cam.setCamera();

    initializeTextures();*/

}



void ECS_SYSTEM::Renderer::render()
{
    static auto tFrame = qint64{0};
    static auto tBegin = qint64{0};


    auto tNow = m_ptimer->elapsed();

    if (tBegin == 0.0f){

        tBegin = tFrame = tNow;
        return;

    }

    auto timeDelta = tNow - tBegin;
    tBegin = tNow;

    /*zRotation += zRotationSpeedDegPerMs * timeDelta;
    auto zDelta = zSpeedMeterPerMs * timeDelta; 
    */
    glDepthMask(true);

    glClearColor(0.0f, 0.5f, 0.7f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //glEnable(GL_DEPTH_TEST);



    /*program1.bind();
    {

        m_cam.setCameraPositionDelta(0.0f, 0.0f, zDelta);

        auto mtxReference = m_cam.getCamera();
        mtxReference.rotate(75.0f, 1.0f, 0.0f, 0.0f);
        mtxReference.rotate(zRotation, 0.0, 0.0, 1.0f);

        program1.setUniformValue(matrixUniform1, mtxReference);
        paintQtLogo();
    
    }

    program1.release();
    */



    //glDisable(GL_DEPTH_TEST);


}


bool ECS_SYSTEM::Renderer::event( QEvent* event )
{

    auto et = event->type();
    if( et == QEvent::KeyPress || et == QEvent::KeyRelease){
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>( event );

        if ( keyEvent->key() == Qt::Key_Up ) { return true;}
        else if ( keyEvent->key() == Qt::Key_Down ) { return true;}
        else if ( keyEvent->key() == Qt::Key_Left ) {

            return true;
        }
        else if ( keyEvent->key() == Qt::Key_Right ) {

            return true;
        }
        else if ( keyEvent->key() == Qt::Key_Escape ) { return true;}


    }

    return false;
}
