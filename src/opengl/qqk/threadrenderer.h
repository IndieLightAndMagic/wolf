

#ifndef THREADRENDERER_H
#define THREADRENDERER_H

#include <QString>
#include <QQuickItem>

namespace HDC{
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
        Q_INVOKABLE void setPropertyString(const QString& propertyName, const QString& propertyValue);
        Q_INVOKABLE void setPropertyReal(const QString& propertyName, const qreal& propertyValue);
        Q_INVOKABLE void setPropertyInteger(const QString& propertyName, const int& propertyValue);


    signals:
        void textureNameChanged(); 

    public Q_SLOTS:
        void ready();

    protected:
        QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *);

    private:
        SceneRenderThread *m_renderThread;
        QString m_textureName;
    };

}

#endif
