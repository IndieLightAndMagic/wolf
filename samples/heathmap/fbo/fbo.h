//
// Created by Guarin on 2019-05-14.
//

#ifndef COURTDEMO_FBO_H
#define COURTDEMO_FBO_H

#include <QQuickFramebufferObject>
namespace HDC{
    class fbo : public QQuickFramebufferObject {
    Q_OBJECT

        Q_PROPERTY(float distance READ distance WRITE setdistance NOTIFY distanceChanged)

    public:
        explicit fbo(QQuickItem *parent = 0);
        Renderer *createRenderer() const Q_DECL_OVERRIDE;

        float distance() const;

    signals:
        void distanceChanged(float distance);

    public slots:
        void setdistance(float distance);

    private:
        float m_distance;
    };

}


#endif //COURTDEMO_FBO_H
