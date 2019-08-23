

#ifndef THREADRENDERER_H
#define THREADRENDERER_H

#include <QString>
#include <QQuickItem>


#include "collader.h"

namespace QQE{
    class SceneRenderThread;
    class SceneRenderer : public QQuickItem
    {
        Q_OBJECT
        Q_PROPERTY(QString textureName READ textureName WRITE setTextureName NOTIFY textureNameChanged)

    public:
        SceneRenderer();
        static QList<QThread *> threads;
        
        QString textureName();
        virtual void setTextureName(const QString& textureName);
        
        Q_INVOKABLE void keyPressed(int keypressed_code);
        Q_INVOKABLE void loadCollada(QString resourceName);

    signals:
        void textureNameChanged(); 

    public Q_SLOTS:
        void ready();

    protected:
        QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *);

    private:
        SceneRenderThread *m_renderThread;
        QString m_textureName;
        QQE::ColladaVisitor* pVisitor{nullptr};

    };

}

#endif
