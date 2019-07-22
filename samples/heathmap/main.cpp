
#include "threadrenderer.h"

#include <QThread>
#include <QQuickView>
#include <QQmlEngine>
#include <QSurfaceFormat>
#include <QGuiApplication>


#include "loggingrectangletest.h"


int main(int argc, char **argv){
    QGuiApplication app(argc, argv);


    qmlRegisterType<HDC::SceneRenderer>("SceneGraphRendering", 1, 0, "SceneRender");
    int execReturn = 0;
    {
        //Scoped view with a threaded renderer so it would be killed at the end of this scope.
        QQuickView view;

        // Rendering in a thread introduces a slightly more complicated cleanup
        // so we ensure that no cleanup of graphics resources happen until the
        // application is shutting down.
        view.setPersistentOpenGLContext(true);
        view.setPersistentSceneGraph(true);

        view.setResizeMode(QQuickView::SizeRootObjectToView);
        view.setSource(QUrl("samples/heathmap/qml/src/main.qml"));
        view.show();

        LoggingRectangle::install(view, "drawer.loggingRectangle");
        execReturn = app.exec();
    }

    //Join all the scene renderers over there.
    for (QThread *t : qAsConst(HDC::SceneRenderer::threads)) {
        t->wait();
        delete t;
    }

    return execReturn;

}










