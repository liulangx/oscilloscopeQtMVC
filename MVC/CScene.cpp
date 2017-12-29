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
    if(m_flagDraw)
    {
        drawAxis(m_index);
    }
    painter->endNativePainting();
//    double time_End = (double)::clock();
    /*gettimeofday(&tpend,NULL);
    timeuse=(1000000*(tpend.tv_sec-tpstart.tv_sec) + tpend.tv_usec-tpstart.tv_usec)/1000000.0;

    qDebug()<<timeuse<<"s";*/


//    qDebug() << (time_End - time_Start) / 1000.0 << "s";
//    qDebug() << time.elapsed() / 1000.0 << "s";
}

void CScene::genAxis(u_short _index)
{
    vector<GLuint> m_arrowIndex;
    vector<float> m_arrowpoint;
    vector2f m_arrowbase = m_arrowbases.at(_index);
    m_arrowIndex.clear();
    m_arrowpoint.clear();

    size_t anglenum = 20;
    int offsite = 0;
    for (size_t index = 0; index < anglenum; ++index)		//��������
    {
        if (index < (anglenum - 1))
        {
            m_arrowIndex.push_back(0);
            m_arrowIndex.push_back(index + 1);
            m_arrowIndex.push_back(index + 2);
        }
        else {
            m_arrowIndex.push_back(0);
            m_arrowIndex.push_back(index + 1);
            m_arrowIndex.push_back(1);
        }
    }
    offsite = anglenum + 1;
    for (size_t index = 0; index < anglenum; ++index)		//��������
    {
        if (index < (anglenum - 1))
        {
            m_arrowIndex.push_back(0 + offsite);
            m_arrowIndex.push_back(index + 1 + offsite);
            m_arrowIndex.push_back(index + 2 + offsite);
        }
        else {
            m_arrowIndex.push_back(0 + offsite);
            m_arrowIndex.push_back(index + 1 + offsite);
            m_arrowIndex.push_back(1 + offsite);
        }
    }
    offsite = 2 * (anglenum + 1);
    for (size_t index = 0; index < anglenum; ++index)		//��������
    {
        if (index < (anglenum - 1))
        {
            m_arrowIndex.push_back(0 + offsite);
            m_arrowIndex.push_back(index + 1 + offsite);
            m_arrowIndex.push_back(index + 2 + offsite);
        }
        else {
            m_arrowIndex.push_back(0 + offsite);
            m_arrowIndex.push_back(index + 1 + offsite);
            m_arrowIndex.push_back(1 + offsite);
        }
    }
    offsite = 3 * (anglenum + 1);
    for (size_t index = 0; index < 6 * 3; ++index)					//����������
    {
        m_arrowIndex.push_back(offsite + index);
    }

    vector2f m_x = m_xs.at(_index);
    vector2f m_y = m_ys.at(_index);
    vector2f m_z = m_zs.at(_index);
    vector4f m_xcolor = m_xcolors.at(_index);
    vector4f m_ycolor = m_ycolors.at(_index);
    vector4f m_zcolor = m_zcolors.at(_index);
    //X�����ͷ
    m_arrowpoint.push_back(m_x._y);			//x���
    m_arrowpoint.push_back(m_y._x);			//y��С
    m_arrowpoint.push_back(m_z._x);			//z��С
    m_arrowpoint.push_back(m_xcolor._r);//��ɫ
    m_arrowpoint.push_back(m_xcolor._g);//��ɫ
    m_arrowpoint.push_back(m_xcolor._b);//��ɫ
    m_arrowpoint.push_back(m_xcolor._a);//��ɫ
    for (size_t index = 0; index < anglenum; ++index)
    {
        m_arrowpoint.push_back(m_x._y - m_arrowbase._y);
        m_arrowpoint.push_back(m_y._x+m_arrowbase._x*cos(index * 2 * pi / anglenum));
        m_arrowpoint.push_back(m_z._x+m_arrowbase._x*sin(index * 2 * pi / anglenum));

        m_arrowpoint.push_back(m_xcolor._r);//��ɫ
        m_arrowpoint.push_back(m_xcolor._g);//��ɫ
        m_arrowpoint.push_back(m_xcolor._b);//��ɫ
        m_arrowpoint.push_back(m_xcolor._a);//��ɫ
    }

    //Y���� ��ͷ
    m_arrowpoint.push_back(m_x._x);			//x���
    m_arrowpoint.push_back(m_y._y);			//y��С
    m_arrowpoint.push_back(m_z._x);			//z��С
    m_arrowpoint.push_back(m_ycolor._r);//��ɫ
    m_arrowpoint.push_back(m_ycolor._g);//��ɫ
    m_arrowpoint.push_back(m_ycolor._b);//��ɫ
    m_arrowpoint.push_back(m_ycolor._a);//��ɫ
    for (size_t index = 0; index < anglenum; ++index)
    {
        m_arrowpoint.push_back(m_x._x + m_arrowbase._x*cos(index * 2 * pi / anglenum));
        m_arrowpoint.push_back(m_y._y - m_arrowbase._y);
        m_arrowpoint.push_back(m_z._x + m_arrowbase._x*sin(index * 2 * pi / anglenum));

        m_arrowpoint.push_back(m_ycolor._r);//��ɫ
        m_arrowpoint.push_back(m_ycolor._g);//��ɫ
        m_arrowpoint.push_back(m_ycolor._b);//��ɫ
        m_arrowpoint.push_back(m_ycolor._a);//��ɫ
    }

    //Z���� ��ͷ
    m_arrowpoint.push_back(m_x._x);
    m_arrowpoint.push_back(m_y._x);
    m_arrowpoint.push_back(m_z._y);
    m_arrowpoint.push_back(m_zcolor._r);//��ɫ
    m_arrowpoint.push_back(m_zcolor._g);//��ɫ
    m_arrowpoint.push_back(m_zcolor._b);//��ɫ
    m_arrowpoint.push_back(m_zcolor._a);//��ɫ
    for (size_t index = 0; index < anglenum; ++index)
    {
        m_arrowpoint.push_back(m_x._x + m_arrowbase._x*cos(index * 2 * pi / anglenum));
        m_arrowpoint.push_back(m_y._x - m_arrowbase._x*sin(index * 2 * pi / anglenum));
        m_arrowpoint.push_back(m_z._y - m_arrowbase._y);
        m_arrowpoint.push_back(m_zcolor._r);//��ɫ
        m_arrowpoint.push_back(m_zcolor._g);//��ɫ
        m_arrowpoint.push_back(m_zcolor._b);//��ɫ
        m_arrowpoint.push_back(m_zcolor._a);//��ɫ
    }

    //X��
    m_arrowpoint.push_back(m_x._x); m_arrowpoint.push_back(m_y._x); m_arrowpoint.push_back(m_z._x);
    m_arrowpoint.push_back(m_xcolor._r); m_arrowpoint.push_back(m_xcolor._g); m_arrowpoint.push_back(m_xcolor._b); m_arrowpoint.push_back(m_xcolor._a);

    m_arrowpoint.push_back(m_x._y); m_arrowpoint.push_back(m_y._x); m_arrowpoint.push_back(m_z._x);
    m_arrowpoint.push_back(m_xcolor._r); m_arrowpoint.push_back(m_xcolor._g); m_arrowpoint.push_back(m_xcolor._b); m_arrowpoint.push_back(m_xcolor._a);
    //Y��
    m_arrowpoint.push_back(m_x._x); m_arrowpoint.push_back(m_y._x); m_arrowpoint.push_back(m_z._x);
    m_arrowpoint.push_back(m_ycolor._r); m_arrowpoint.push_back(m_ycolor._g); m_arrowpoint.push_back(m_ycolor._b); m_arrowpoint.push_back(m_ycolor._a);

    m_arrowpoint.push_back(m_x._x); m_arrowpoint.push_back(m_y._y); m_arrowpoint.push_back(m_z._x);
    m_arrowpoint.push_back(m_ycolor._r); m_arrowpoint.push_back(m_ycolor._g); m_arrowpoint.push_back(m_ycolor._b); m_arrowpoint.push_back(m_ycolor._a);
    //Z��
    m_arrowpoint.push_back(m_x._x); m_arrowpoint.push_back(m_y._x); m_arrowpoint.push_back(m_z._x);
    m_arrowpoint.push_back(m_zcolor._r); m_arrowpoint.push_back(m_zcolor._g); m_arrowpoint.push_back(m_zcolor._b); m_arrowpoint.push_back(m_zcolor._a);

    m_arrowpoint.push_back(m_x._x); m_arrowpoint.push_back(m_y._x); m_arrowpoint.push_back(m_z._y);
    m_arrowpoint.push_back(m_zcolor._r); m_arrowpoint.push_back(m_zcolor._g); m_arrowpoint.push_back(m_zcolor._b); m_arrowpoint.push_back(m_zcolor._a);
    m_arrowIndexs.insert(std::pair<u_short, vector<GLuint>>(_index, m_arrowIndex));
    m_arrowpoints.insert(std::pair<u_short, vector<float>>(_index, m_arrowpoint));
}

void CScene::drawAxis(u_short _index)
{
    GLuint m_vao = m_vaos.at(_index);
    GLuint m_vbo = m_vbos.at(_index);
    GLuint m_vboIndex = m_vboIndexs.at(_index);
    qDebug() << _index;
    m_widget->makeCurrent();
    m_therenders.at(_index)->bindShader();
    m_therenders.at(_index)->getShader()->setUniformValue(m_uniformIndexRotPntAnixGrids.at(_index), m_rotations.at(_index));
    glBindVertexArray(m_vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,
        m_vboIndex);
    glDrawElements(GL_TRIANGLES,m_arrowIndexs.at(_index).size()-18, GL_UNSIGNED_INT, 0);
    glLineWidth(1.5);
    glDrawElements(GL_LINES, 18, GL_UNSIGNED_INT, (char*)((m_arrowIndexs.at(_index).size() - 18)*4));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); //ll
    glBindVertexArray(0);
    m_therenders.at(_index)->releaseShader();
    qDebug() << _index;
}

void CScene::genAxisBuffer(u_short _index)
{
    GLuint m_vao = m_vaos.at(_index);
    GLuint m_vbo = m_vbos.at(_index);
    GLuint m_vboIndex = m_vboIndexs.at(_index);

    glBindVertexArray(m_vao);
    GLuint _persize = sizeof(vector3f) + sizeof(vector4f);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER,
        m_arrowpoints.at(_index).size() * sizeof(GLfloat),
        m_arrowpoints.at(_index).data(),
        GL_DYNAMIC_DRAW);
//    GLint size = 0;
//    glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,
        3,
        GL_FLOAT,
        GL_FALSE,
        _persize,
        0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,
        4,
        GL_FLOAT,
        GL_FALSE,
        _persize,
        (char*)(sizeof(vector3f)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,
        m_vboIndex);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
        m_arrowIndexs.at(_index).size() * sizeof(GLuint),
        m_arrowIndexs.at(_index).data(),
        GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
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
        m_index = 0;
}

void CScene::initGL(u_short _index)
{
    m_widget->makeCurrent();
    initializeOpenGLFunctions();

    vector2f m_x = {0, 1};
    m_xs.insert(std::pair<u_short, vector2f>(_index, m_x));
    vector2f m_y = {0, 1};
    m_ys.insert(std::pair<u_short, vector2f>(_index, m_y));
    vector2f m_z = {0, 1};
    m_zs.insert(std::pair<u_short, vector2f>(_index, m_z));
    vector2f m_arrowbase = {0.01f,0.05f};
    m_arrowbases.insert(std::pair<u_short,vector2f>(_index, m_arrowbase));
//    GLboolean m_flagDraw = false;
//    m_flagDraws.insert(std::pair<u_short, GLboolean>(_index, m_flagDraw));
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

    if(_index == 0)
    {
        vector4f m_xcolor = {1, 0, 0, 1};
        m_xcolors.insert(std::pair<u_short, vector4f>(_index, m_xcolor));
        vector4f m_ycolor = {0, 0, 0, 1};
        m_ycolors.insert(std::pair<u_short, vector4f>(_index, m_ycolor));
        vector4f m_zcolor = {0, 0, 0, 1};
        m_zcolors.insert(std::pair<u_short, vector4f>(_index, m_zcolor));
    }
    else if(_index == 1)
    {
        vector4f m_xcolor = {0, 0, 0, 1};
        m_xcolors.insert(std::pair<u_short, vector4f>(_index, m_xcolor));
        vector4f m_ycolor = {0, 1, 0, 1};
        m_ycolors.insert(std::pair<u_short, vector4f>(_index, m_ycolor));
        vector4f m_zcolor = {0, 0, 0, 1};
        m_zcolors.insert(std::pair<u_short, vector4f>(_index, m_zcolor));
    }
    else
    {
        vector4f m_xcolor = {0, 0, 0, 1};
        m_xcolors.insert(std::pair<u_short, vector4f>(_index, m_xcolor));
        vector4f m_ycolor = {0, 0, 0, 1};
        m_ycolors.insert(std::pair<u_short, vector4f>(_index, m_ycolor));
        vector4f m_zcolor = {0, 0, 1, 1};
        m_zcolors.insert(std::pair<u_short, vector4f>(_index, m_zcolor));
    }

    CRender* m_therender = new CRender;
    m_therenders.insert(std::pair<u_short, CRender*>(_index, m_therender));
    m_therender->prepare();

    GLuint m_vao, m_vbo, m_vboIndex;

    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_vboIndex);

    m_vaos.insert(std::pair<u_short, GLuint>(_index, m_vao));
    m_vbos.insert(std::pair<u_short, GLuint>(_index, m_vbo));
    m_vboIndexs.insert(std::pair<u_short, GLuint>(_index, m_vboIndex));

    genAxis(_index);
    genAxisBuffer(_index);
   /* GLboolean*/ m_flagDraw = true;
//    m_flagDraws.insert(std::pair<u_short, GLboolean>(m_index, ))
    //m_timer->start();

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
