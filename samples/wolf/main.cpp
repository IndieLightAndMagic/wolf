#include "threadrenderer.h"

#include <QThread>
#include <QQuickView>
#include <QQmlEngine>
#include <QSurfaceFormat>
#include <QGuiApplication>


class QQE {

private:
    QQE(){

    }
public:
    static QQE*CreateQQE(){
        
    }
}

int main(int argc, char **argv){

    QGuiApplication app(argc, argv);


    qmlRegisterType<HDC::SceneRenderer>("SceneGraphRendering", 1, 0, "SceneRender");
    int execReturn = 0;

    {
        QQuickView view;

        // Rendering in a thread introduces a slightly more complicated cleanup
        // so we ensure that no cleanup of graphics resources happen until the
        // application is shutting down.
        view.setPersistentOpenGLContext(true);
        view.setPersistentSceneGraph(true);

        view.setResizeMode(QQuickView::SizeRootObjectToView);
        view.setSource(QUrl("../samples/heathmap/qml/src/main.qml"));
        view.show();

        execReturn = app.exec();
    }

    // As the render threads make use of our QGuiApplication object
    // to clean up gracefully, wait for them to finish before
    // QGuiApp is taken off the heap.
    for (QThread *t : qAsConst(HDC::SceneRenderer::threads)) {
        t->wait();
        delete t;
    }

    return execReturn;

}










