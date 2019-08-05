#ifndef __ECSSYSTEM_RENDER_H__
#define __ECSSYSTEM_RENDER_H__
#include <QtGui/qvector3d.h>
#include <QtGui/qmatrix4x4.h>
#include <QtGui/qopenglshaderprogram.h>
#include <QtGui/qopenglfunctions.h>

#include <QTime>
#include <QEvent>
#include <QVector>
#include <QElapsedTimer>
#include <src/meshes/geometry120.h>
#include <src/camera/camera.h>
#include <src/texture/fastqtexturedata.h>

#include "ecs/System.h"

namespace ECS_SYSTEM{

    class Renderer : public QObject, QOpenGLFunctions, ECS_SYSTEM::System
    {
        Q_OBJECT
    public:
        Renderer(QObject* parent = nullptr);
        virtual ~Renderer();

        virtual void render();
        virtual void initialize();

        void AddComponent(int componentId) override;

    protected:
        bool event(QEvent *event) override;

    private:
        QElapsedTimer* m_ptimer{nullptr};


    };
}

#endif /* __ECS_SSYSTEM_RENDER_H__
 */
