#ifndef CSCENEMANAGER_H
#define CSCENEMANAGER_H
//#include "CAxis.h"
#include "AxisAndGrid/CAxisManager.h"
#include "CGridManager.h"
#include "CLineManager.h"

#include <QOpenGLFunctions_4_3_Core>
#include <QGLWidget>
#include <QGraphicsSceneMouseEvent>
#include <map>
using std::map;
class CScene;

class CSceneManager : public QObject, public QOpenGLFunctions_4_3_Core
{
    Q_OBJECT
public:
    explicit CSceneManager(CScene* _mvcWidget, QGLWidget* _widget);
    //初始化
    void initGL(u_short _index);
    void prepareDataForEachImg(u_short _index);
    void prepareAxis(u_short _index);
    void prepareLine(u_short _index);
    void prepareGrid(u_short _index);
    void draw();

    //设置旋转矩阵
    void setRot(float _x, float _y);
    void setMove(float _x, float _y);
    void setDrawType(CGrid::DRAWTYPE _drawtype);
    void addPoint(size_t _lineindex, const vector3f &_position);

//    void setRotation(u_short _index, QMatrix4x4 _rotation);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void WheelEvent(QGraphicsSceneWheelEvent *event);
public slots:
    void onAdjustGridNumer(u_short _imgIndex, vector2f _xrange, vector2f _yrange, vector2f _zrange, CGrid::RangeChange _xRanChange, CGrid::RangeChange _yRanChange, CGrid::RangeChange _zRanChange);
signals:
    void update();
private:
    u_short m_index = 0;

    GLboolean                    m_flagDraw = false;
    CGrid::DRAWTYPE             m_drawtype = CGrid::DRAWTYPE::XZY;

//    map<u_short, CRender*>                       m_therenders;
    //CRender
//    map<u_short, GLuint>						m_uniformIndexRotPntAnixGrids;
    map<u_short, QMatrix4x4>          m_rotations;/* = {
                                1, 0, 0, 0,
                                0, 1, 0, 0,
                                0, 0, 1, 0,
                                0, 0, 0, 1
                            };*/
    map<u_short, QMatrix4x4>          m_moves;

    map<u_short, bool>	m_leftPushDowns/* = false*/;		//左键按下
    map<u_short, bool>	m_rightPushDowns/* = false*/;	//右键按下
    map<u_short, int>		m_mouseCordxs/* = 0*/;			//左键鼠标位置x
    map<u_short, int>		m_mouseCordys/* = 0*/;			//左键鼠标位置y
    map<u_short, u_char> m_frameTypes/* = 0*/;
//    CAxis*    m_axis;
    CAxisManager*  m_axisManager;
    CLineManager*  m_lineManager;
    CGridManager*   m_gridManager;
    QGLWidget* m_glwidget;
    CVaoVboManager* m_vaovboManager;
};

#endif // CSCENEMANAGER_H
