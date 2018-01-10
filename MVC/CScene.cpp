/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the demonstration applications of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

//#include <QDebug>
#include "MVC/CScene.h"

#define pi 3.1415926

CScene::CScene(int width, int height, QGLWidget *_widget)
    : m_widget(_widget)
    , m_sceneManager(new CSceneManager(this, m_widget))
    , m_insQtWinManager(new CInsQtWinManager(this))
{
    setSceneRect(0, 0, width, height);
}

CScene::~CScene()
{
    this->cleanUp();
}

void CScene::cleanUp()
{

}

void CScene::drawBackground(QPainter *painter, const QRectF &)
{
//    QTime time;
//    time.start();
//    double time_Start = (double)::clock();
//    struct timeval tpstart,tpend;
//    float timeuse;
//    gettimeofday(&tpstart,NULL);
    painter->beginNativePainting();

    m_sceneManager->draw();

    painter->endNativePainting();
//    double time_End = (double)::clock();
    /*gettimeofday(&tpend,NULL);
    timeuse=(1000000*(tpend.tv_sec-tpstart.tv_sec) + tpend.tv_usec-tpstart.tv_usec)/1000000.0;

    qDebug()<<timeuse<<"s";*/


//    qDebug() << (time_End - time_Start) / 1000.0 << "s";
//    qDebug() << time.elapsed() / 1000.0 << "s";
}

void CScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mousePressEvent(event);
    if(event->isAccepted())
        return;
    m_sceneManager->mousePressEvent(event);
}

void CScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseMoveEvent(event);
    if(event->isAccepted())
        return;
    m_sceneManager->mouseMoveEvent(event);
    update();

}

void CScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseReleaseEvent(event);
    if(event->isAccepted())
        return;
    m_sceneManager->mouseReleaseEvent(event);
}

void CScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseDoubleClickEvent(event);
    if(event->isAccepted())
        return;
    m_sceneManager->mouseDoubleClickEvent(event);
}

void CScene::wheelEvent(QGraphicsSceneWheelEvent *event)
{
    QGraphicsScene::wheelEvent(event);
    if(event->isAccepted())
        return;
    m_sceneManager->WheelEvent(event);
}

void CScene::initGL(u_short _index)
{
    m_widget->makeCurrent();
    initializeOpenGLFunctions();
    m_sceneManager->initGL(_index);
    m_insQtWinManager->initGL(_index);
//    prepareAxis(_index);
}


bool CScene::addPoint(u_short _imgIndex, size_t _lineindex, const vector3f &_position)
{
    return m_sceneManager->addPoint(_imgIndex, _lineindex, _position);
}

void CScene::setColor(u_short _imgIndex, size_t _lineIndex, vector4f _color)
{
    m_sceneManager->setColor(_imgIndex, _lineIndex, _color);
}

void CScene::onNewItemTriggered(ItemDialog::ItemType _type, u_short _index)
{
    switch (_type) {
    case ItemDialog::ItemType::MakeCurrent:
    {
        m_sceneManager->setCurrentShowIndex(_index);
        break;
    }
    case ItemDialog::ItemType::HoVAxis:
    {
        m_sceneManager->setAxisHideOrShow(_index);
        break;
    }
    case ItemDialog::ItemType::HoVGrid:
    {
        m_sceneManager->setGridHideOrShow(_index);
        break;
    }
    case ItemDialog::ItemType::HoVXY:
    {
        m_sceneManager->setXYHideOrShow(_index);
        break;
    }
    case ItemDialog::ItemType::HoVXZ:
    {
        m_sceneManager->setXZHideOrShow(_index);
        break;
    }
    case ItemDialog::ItemType::HoVYZ:
    {
        m_sceneManager->setYZHideOrShow(_index);
        break;
    }
    default:
        break;
    }
}

//void CScene::onRotationChanged(QMatrix4x4 _rotation)
//{
//    m_rotation = _rotation;
//    update();
//}
