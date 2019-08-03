
#include "threadrenderer.h"

#include <QThread>
#include <QQuickView>
#include <QQmlEngine>
#include <QSurfaceFormat>
#include <QGuiApplication>
#include <QLibraryInfo>
#include <QDirIterator>


#include "loggingrectangletest.h"


int main(int argc, char **argv){
    QGuiApplication app(argc, argv);


    qmlRegisterType<QQE::SceneRenderer>("SceneGraphRendering", 1, 0, "SceneRender");
    int execReturn = 0;
    {
        //Scoped view with a threaded renderer so it would be killed at the end of this scope.
        QQuickView view;


        auto pEngine = view.engine();
        auto importPaths = pEngine->importPathList();

        for (auto&path:importPaths){
            qInfo() << path;
        }

        qInfo() << QLibraryInfo::location(QLibraryInfo::Qml2ImportsPath);
        qInfo() << ".....";

        QDirIterator it("/qt-project.org/imports", QDirIterator::Subdirectories);while(it.hasNext()){
            qInfo() << it.next();
        }

        qInfo() << ".....";

        auto argumentCount = 0;
        while(argumentCount < argc){

            qInfo() << argumentCount << " " << argv[argumentCount];
            argumentCount++;

        }


        auto resourcesToBeLoaded = QList<QString>{
            "qrc:src/main.qml"
        };

        for (auto& resourceToBeLoaded:resourcesToBeLoaded){

            auto resourceUrl = QUrl(resourceToBeLoaded);
            auto resourcePath = QDir(resourceUrl.path());
            auto resourceAbsolutePath = resourcePath.absolutePath();
            auto resourceAbsolutePathString = resourceAbsolutePath.toStdString();
            qInfo() << "Resource to be loaded: " << resourceToBeLoaded;
            qInfo() << "Resource path: " << resourcePath;
            qInfo() << "Resource Absolute Path: " << resourceAbsolutePath;

        }
        // Rendering in a thread introduces a slightly more complicated cleanup
        // so we ensure that no cleanup of graphics resources happen until the
        // application is shutting down.
        view.setPersistentOpenGLContext(true);
        view.setPersistentSceneGraph(true);

        view.setResizeMode(QQuickView::SizeRootObjectToView);
        view.setSource(QUrl("src/main.qml"));
        view.show();

        LoggingRectangle::install(view, "drawer.loggingRectangle");
        execReturn = app.exec();

    }

    //Join all the scene renderers over there.
    for (QThread *t : qAsConst(QQE::SceneRenderer::threads)) {

        t->wait();
        delete t;

    }

    return execReturn;

}










