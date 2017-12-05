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

#include <QDebug>
#include "scene.h"
#include <GL/glu.h>
#define pi 3.1415926

Scene::Scene(int width, int height, int maxTextureSize, QGLWidget *_widget)
{
    setSceneRect(0, 0, width, height);
    m_widget = _widget;

    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));
    m_timer->setInterval(20);
//    m_timer->start();

}

Scene::~Scene()
{

}
void Scene::setStates()
{
    //glClearColor(0.25f, 0.25f, 0.5f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);
    //glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_NORMALIZE);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

//    setLights();

    float materialSpecular[] = {0.5f, 0.5f, 0.5f, 1.0f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialSpecular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 32.0f);
}

void Scene::drawBackground(QPainter *painter, const QRectF &)
{
    float width = float(painter->device()->width());
    float height = float(painter->device()->height());


    painter->beginNativePainting();
//    glPushAttrib(GL_ALL_ATTRIB_BITS);
    if(m_draw)
    {
        drawAnix();
    }
//    glPopAttrib();
    painter->endNativePainting();
    //glClearColor(1,1,1,1);
//       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//       glMatrixMode(GL_PROJECTION);
//       glPushMatrix();
//       glLoadIdentity();
//       //gluOrtho2D(0,1,0,1);

//       glMatrixMode(GL_MODELVIEW);
//       glPushMatrix();
//       glLoadIdentity();

////       glColor3f(1,0,0);
////       glLineWidth(2);

//       float margin=0.05;
//       float l=margin,r=1-margin,b=margin,t=1-margin;
//       int splitNum=9;
//       float dx=(1-margin*2)/(splitNum+1);

//           if(m_draw)
//               drawAnix();
//       glPopMatrix();

//       glMatrixMode(GL_PROJECTION);
//       glPopMatrix();
}

void Scene::genAnix()
{
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

}

void Scene::drawAnix()
{
    m_widget->makeCurrent();
    m_therender.bindShader();
    m_therender.getShader()->setUniformValue(m_uniformIndexRotPntAnixGrid, m_rotation);
    glBindVertexArray(m_vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,
        m_vboIndex);
    glDrawElements(GL_TRIANGLES,m_arrowIndex.size()-18, GL_UNSIGNED_INT, 0);
    glLineWidth(1.5);
    glDrawElements(GL_LINES, 18, GL_UNSIGNED_INT, (char*)((m_arrowIndex.size() - 18)*4));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); //ll
    glBindVertexArray(0);
    m_therender.releaseShader();
}

void Scene::genBuffer()
{
    glBindVertexArray(m_vao);
    GLuint _persize = sizeof(vector3f) + sizeof(vector4f);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER,
        m_arrowpoint.size() * sizeof(GLfloat),
        m_arrowpoint.data(),
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
        m_arrowIndex.size() * sizeof(GLuint),
        m_arrowIndex.data(),
        GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_leftPushDown = true;
        m_mouseCordx = event->scenePos().x();
        m_mouseCordy = event->scenePos().y();
    }
    if (event->button() == Qt::RightButton)
    {
        m_rightPushDown = true;
        m_mouseCordx = event->scenePos().x();
        m_mouseCordy = event->scenePos().y();
    }
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(0 == m_frameType)
    {
        if (m_leftPushDown)
        {
            float _roatx = m_mouseCordx - event->scenePos().x();
            float _roaty = m_mouseCordy - event->scenePos().y();
            m_mouseCordx = event->scenePos().x();
            m_mouseCordy = event->scenePos().y();
            setRot(_roaty / 200,  _roatx/ 200/*,0*/);
        }
    }
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_leftPushDown = false;
    }
    if (event->button() == Qt::RightButton)
    {
        m_rightPushDown = false;
    }
}

void Scene::initGL()
{
    initializeOpenGLFunctions();
    m_widget->makeCurrent();
    m_therender.prepare();

    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_vboIndex);
    genAnix();
    genBuffer();

    m_draw = true;
    m_timer->start();


    m_uniformIndexRotPntAnixGrid= m_therender.getShader()->uniformLocation("rot");

    m_therender.bindShader();			//����shader
    m_therender.getShader()->setUniformValue(m_uniformIndexRotPntAnixGrid, m_rotation);
    m_therender.releaseShader();

}

void Scene::setRot(float _x, float _y)
{
    m_rotation = QMatrix4x4(1.0, 0.0, 0.0, 0.0,
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
                    0.0, 0.0, 0.0, 1.0)*/*m_rotation;
    update();
}
