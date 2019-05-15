//
// Created by Guarin on 2019-05-14.
//

#include "fbo.h"
/****************************************************************************
**
** Copyright (C) 2017 Klarälvdalens Datakonsult AB, a KDAB Group company.
** Author: Giuseppe D'Angelo
** Contact: info@kdab.com
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************/

#include "fbo.h"
#include "heatmapscene.h"

#include <QtQuick>
#include <QQuickWindow>
#include <QOpenGLFramebufferObject>
#include <QOpenGLFramebufferObjectFormat>

namespace HDC{
    class fborenderer: public QQuickFramebufferObject::Renderer
    {
    public:
        fborenderer()
        {
            m_render.initialize();
        }

        void synchronize(QQuickFramebufferObject *item) Q_DECL_OVERRIDE
        {
            m_window = item->window();

            fbo *i = static_cast<fbo *>(item);
            m_render.setdistance(i->distance());
        }

        void render() Q_DECL_OVERRIDE
        {
            m_render.render();
            m_window->resetOpenGLState();
        }

        QOpenGLFramebufferObject *createFramebufferObject(const QSize &size) Q_DECL_OVERRIDE
        {
            QOpenGLFramebufferObjectFormat format;
            format.setSamples(4);
            format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
            return new QOpenGLFramebufferObject(size, format);
        }

    private:
        HDC::HeatMapScene m_render;
        QQuickWindow *m_window;
    };



}


// fbo implementation

HDC::fbo::fbo(QQuickItem *parent)
        : QQuickFramebufferObject(parent)
        , m_distance(5.0)
{
    setMirrorVertically(true);
}

QQuickFramebufferObject::Renderer* HDC::fbo::createRenderer() const
{
    return new fborenderer;
}


float HDC::fbo::distance() const
{
    return m_distance;
}


void HDC::fbo::setdistance(float distance)
{
    if (m_distance == distance)
        return;

    m_distance = distance;
    emit distanceChanged(distance);
    update();
}

