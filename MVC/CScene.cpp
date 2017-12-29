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
{
    setSceneRect(0, 0, width, height);
    m_widget = _widget;

    CGraphicsWidget * widgetP = new CGraphicsWidget;
    ItemDialog* itemDialog = new ItemDialog;
//    widgetP->setCacheMode(QGraphicsItem::ItemCoordinateCache);
//    widgetP->setZValue(1e30);
//    widgetP->setWidget(itemDialog);
    itemDialog->move(100, 160);
    itemDialog->resize(itemDialog->sizeHint());
    itemDialog->setWindowTitle("This is a test");
//    widgetP->setVisible(true);

    ItemDialog* itemDialog1 = new ItemDialog;


    CTwoSidedGraphicsWidget *twoSided = new CTwoSidedGraphicsWidget(this);
    twoSided->setWidget(0, itemDialog);
    twoSided->setWidget(1, itemDialog1);
    CTwoSidedGraphicsWidget *twoSided1 = new CTwoSidedGraphicsWidget(this);


    ItemDialog* itemDialog2 = new ItemDialog;
    ItemDialog* itemDialog3 = new ItemDialog;
    twoSided1->setWidget(0, itemDialog2);
    twoSided1->setWidget(1, itemDialog3);
    itemDialog2->move(300, 160);
    itemDialog2->resize(itemDialog2->sizeHint());


    connect(itemDialog, SIGNAL(doubleClicked()), twoSided, SLOT(flip()));
    connect(itemDialog1, SIGNAL(doubleClicked()), twoSided, SLOT(flip()));
    connect(itemDialog2, SIGNAL(doubleClicked()), twoSided1, SLOT(flip()));
    connect(itemDialog3, SIGNAL(doubleClicked()), twoSided1, SLOT(flip()));
//    this->addItem(widgetP);

}

CScene::~CScene()
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
//    if(m_flagDraw)
//    {
    m_therenders.at(m_index)->bindShader();
    m_therenders.at(m_index)->getShader()->setUniformValue(m_uniformIndexRotPntAnixGrids.at(m_index), m_rotations.at(m_index));
//        drawAxis(m_index);
        m_axis->draw();
        m_therenders.at(m_index)->releaseShader();
//    }
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
    if (event->button() == Qt::LeftButton)
    {
        m_leftPushDowns.at(m_index) = true;
        m_mouseCordxs.at(m_index) = event->scenePos().x();
        m_mouseCordys.at(m_index) = event->scenePos().y();
    }
    if (event->button() == Qt::RightButton)
    {
        m_rightPushDowns.at(m_index) = true;
        m_mouseCordxs.at(m_index) = event->scenePos().x();
        m_mouseCordys.at(m_index) = event->scenePos().y();
    }

}

void CScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseMoveEvent(event);
    if(event->isAccepted())
        return;
    if(0 == m_frameTypes.at(m_index))
    {
        if (m_leftPushDowns.at(m_index))
        {
            float _roatx = m_mouseCordxs.at(m_index) - event->scenePos().x();
            float _roaty = m_mouseCordys.at(m_index) - event->scenePos().y();
            m_mouseCordxs.at(m_index) = event->scenePos().x();
            m_mouseCordys.at(m_index) = event->scenePos().y();
            setRot(_roaty / 200,  _roatx/ 200/*,0*/);
        }
    }

}

void CScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseReleaseEvent(event);
    if(event->isAccepted())
        return;
    if (event->button() == Qt::LeftButton)
    {
        m_leftPushDowns.at(m_index) = false;
    }
    if (event->button() == Qt::RightButton)
    {
        m_rightPushDowns.at(m_index) = false;
    }

}

void CScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseDoubleClickEvent(event);
    if(event->isAccepted())
        return;
    if(m_index < 2)
        m_index += 1;
    else
        m_index = 1;
    m_axis->setCurrentIndex(m_index);

}

void CScene::initGL(u_short _index)
{
    m_widget->makeCurrent();
    initializeOpenGLFunctions();
    CVaoVboManager* vaovboManage = new CVaoVboManager;
    vaovboManage->prepare();
    if(!m_axis)
    {
        m_axis = new CAxis(vaovboManage, m_widget);
        m_axis->setCurrentIndex(_index);
        m_index = _index;
    }
    m_axis->createNewAxisForNewIndex(_index);

    QMatrix4x4 m_rotation = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
    m_rotations.insert(std::pair<u_short, QMatrix4x4>(_index, m_rotation));
    bool m_leftPushDown = false;
    bool m_rightPushDown = false;
    int m_mouseCordx = 0;
    int m_mouseCordy = 0;
    u_char m_frameType = 0;
    m_leftPushDowns.insert(std::pair<u_short, bool>(_index, m_leftPushDown));
    m_rightPushDowns.insert(std::pair<u_short, bool>(_index, m_rightPushDown));
    m_mouseCordxs.insert(std::pair<u_short, int>(_index, m_mouseCordx));
    m_mouseCordys.insert(std::pair<u_short, int>(_index, m_mouseCordy));
    m_frameTypes.insert(std::pair<u_short, u_char>(_index, m_frameType));


    CRender* m_therender = new CRender;
    m_therenders.insert(std::pair<u_short, CRender*>(_index, m_therender));
    m_therender->prepare();


    GLuint m_uniformIndexRotPntAnixGrid;
    m_uniformIndexRotPntAnixGrid = m_therenders.at(_index)->getShader()->uniformLocation("rot");
    m_uniformIndexRotPntAnixGrids.insert(std::pair<u_short, GLuint>(_index, m_uniformIndexRotPntAnixGrid));

    m_therenders.at(_index)->bindShader();			//绑定着色器
    m_therenders.at(_index)->getShader()->setUniformValue(m_uniformIndexRotPntAnixGrids.at(_index), m_rotations.at(_index));
    m_therenders.at(_index)->releaseShader();        //解除着色器

}

void CScene::setRot(float _x, float _y)
{
    m_rotations.at(m_index) = QMatrix4x4(1.0, 0.0, 0.0, 0.0,
                    0.0, cos(_x), -sin(_x), 0.0,
                    0.0, sin(_x), cos(_x), 0.0,
                        0.0, 0.0, 0.0, 1.0)*
        QMatrix4x4(cos(_y), 0.0, sin(_y), 0.0,
            0.0, 1.0, 0.0, 0.0,
            -sin(_y), 0.0, cos(_y), 0.0,
            0.0, 0.0, 0.0, 1.0)/**
                QMatrix4x4(cos(_z), -sin(_z), 0.0, 0.0,
                    sin(_z), cos(_z), 0.0, 0.0,
                    0.0, 0.0, 1.0, 0.0,
                    0.0, 0.0, 0.0, 1.0)*/*m_rotations.at(m_index);
    update();
}

//void CScene::onRotationChanged(QMatrix4x4 _rotation)
//{
//    m_rotation = _rotation;
//    update();
//}
