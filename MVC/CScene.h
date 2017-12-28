#pragma once
//#ifndef SCENE_H
//#define SCENE_H
#include "Database.h"
#include <vector>
#include <QtWidgets>
#include <QtOpenGL>
#include <QTimer>
#include <QOpenGLFunctions_4_3_Core>
#include <CRender.h>

using namespace std;

//模型层model
class CScene : public QGraphicsScene, protected QOpenGLFunctions_4_3_Core
{
    Q_OBJECT
public:
    CScene(int width, int height, /*int maxTextureSize, */QGLWidget* _widget);
    ~CScene();
    void drawBackground(QPainter *painter, const QRectF &rect) override;
    void initGL();
    void setRot(float _x, float _y);
public slots:
//    void onRotationChanged(QMatrix4x4 _rotation);

private:
    void genAxis();
    void drawAxis();
    void genAxisBuffer();
    QGLWidget* m_widget;
//    QTimer* m_timer;
    vector2f                    m_x = {0,1};			//坐标X
    vector2f                    m_y = {0,1};			//坐标Y
    vector2f                    m_z = {0,1};			//坐标Z
    vector2f					m_arrowbase = {0.01f,0.05f};		//箭头底半径 箭头长度
    vector<GLuint>				m_arrowIndex;					//箭头检索
    vector<float>				m_arrowpoint;					//箭头的点
    vector4f					m_xcolor = {1, 0, 0, 1};//{45/255.0f,57/255.0f,227/255.0f,1};						//x轴颜色
    vector4f					m_ycolor = {0, 1, 0, 1};//{45/255.0f,57/255.0f,227/255.0f,1};							//y轴颜色
    vector4f					m_zcolor = {0, 0, 1, 1};//{45/255.0f,57/255.0f,227/255.0f,1};	   					//z轴颜色
    float*						m_arrow;						//线段的点

    GLuint						m_vao;
    GLuint						m_vbo;
    GLuint						m_vboIndex;
    GLboolean                   m_flagDraw = false;

    CRender                     m_therender;
    //CRender
    GLuint						m_uniformIndexRotPntAnixGrid;
    QMatrix4x4          m_rotation = {
                                1, 0, 0, 0,
                                0, 1, 0, 0,
                                0, 0, 1, 0,
                                0, 0, 0, 1
                            };

    bool	m_leftPushDown = false;		//左键按下
    bool	m_rightPushDown = false;	//右键按下
    int		m_mouseCordx = 0;			//左键鼠标位置x
    int		m_mouseCordy = 0;			//左键鼠标位置y
    u_char m_frameType = 0;

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

};

//#endif
