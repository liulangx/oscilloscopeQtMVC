#pragma once
//#ifndef SCENE_H
//#define SCENE_H
#include "Database.h"
#include "InsertQtWin/ItemDialog.h"
#include "InsertQtWin/CGraphicsWidget.h"
#include "InsertQtWin/CTwoSidedGraphicsWidget.h"
#include "DataManage/CVaoVboManager.h"
#include "Shaders/CRender.h"
#include "AxisAndGrid/CAxis.h"

#include <GL/glu.h>
#include <QTime>
#include <sys/time.h>
#include <QGraphicsProxyWidget>

#include <vector>
#include <QtWidgets>
#include <QtOpenGL>
#include <QTimer>
#include <QOpenGLFunctions_4_3_Core>
#include <map>

using namespace std;

//模型层model
class CScene : public QGraphicsScene, protected QOpenGLFunctions_4_3_Core
{
    Q_OBJECT
public:
    CScene(int width, int height, /*int maxTextureSize, */QGLWidget* _widget);
    ~CScene();
    void drawBackground(QPainter *painter, const QRectF &rect) override;
    void initGL(u_short _index);
    void setRot(float _x, float _y);
public slots:
//    void onRotationChanged(QMatrix4x4 _rotation);

private:
    QGLWidget* m_widget;
    u_short m_index = 0;
//    map<u_short, vector2f>                    m_xs/* = {0,1}*/;			//坐标X
//    map<u_short,vector2f>                     m_ys/* = {0,1}*/;			//坐标Y
//    map<u_short,vector2f>                     m_zs/* = {0,1}*/;			//坐标Z
//    map<u_short,vector2f>					 m_arrowbases/* = {0.01f,0.05f}*/;		//箭头底半径 箭头长度
//    map<u_short,vector<GLuint>>				 m_arrowIndexs;					//箭头检索
//    map<u_short,vector<float>>				 m_arrowpoints;					//箭头的点
//    map<u_short,vector4f>					 m_xcolors/* = {1, 0, 0, 1}*/;//{45/255.0f,57/255.0f,227/255.0f,1};						//x轴颜色
//    map<u_short,vector4f>					 m_ycolors/* = {0, 1, 0, 1}*/;//{45/255.0f,57/255.0f,227/255.0f,1};							//y轴颜色
//    map<u_short,vector4f>					 m_zcolors/* = {0, 0, 1, 1}*/;//{45/255.0f,57/255.0f,227/255.0f,1};	   					//z轴颜色
//    map<u_short, float*>						m_arrows;						//线段的点

//    map<u_short, GLuint>						m_vaos;
//    map<u_short, GLuint>						m_vbos;
//    map<u_short, GLuint>						m_vboIndexs;
    GLboolean                    m_flagDraw = false;

    map<u_short, CRender*>                       m_therenders;
    //CRender
    map<u_short, GLuint>						m_uniformIndexRotPntAnixGrids;
    map<u_short, QMatrix4x4>          m_rotations;/* = {
                                1, 0, 0, 0,
                                0, 1, 0, 0,
                                0, 0, 1, 0,
                                0, 0, 0, 1
                            };*/

    map<u_short, bool>	m_leftPushDowns/* = false*/;		//左键按下
    map<u_short, bool>	m_rightPushDowns/* = false*/;	//右键按下
    map<u_short, int>		m_mouseCordxs/* = 0*/;			//左键鼠标位置x
    map<u_short, int>		m_mouseCordys/* = 0*/;			//左键鼠标位置y
    map<u_short, u_char> m_frameTypes/* = 0*/;

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

    CAxis*    m_axis;


};

//#endif
