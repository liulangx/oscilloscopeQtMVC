#ifndef CAXISMANAGER_H
#define CAXISMANAGER_H
#include "Shaders/CRender.h"
#include "DataManage/CVaoVboManager.h"
#include "CAxis.h"
#include <QGLWidget>
#include <QOpenGLFunctions_4_3_Core>
#include <map>
using std::map;
class CAxisManager : public QObject, public QOpenGLFunctions_4_3_Core
{
    Q_OBJECT
public:
    enum DRAWTYPE {
        XZY = 0,
        XY,
        XZ,
        YZ
    };
    explicit CAxisManager(CVaoVboManager* _vaovboManager, QGLWidget* _widget);
    ~CAxisManager();
    void initial();
    void draw();
    void setDraw();
    void prepareAxis(u_short _index);
    void setCurIndex(u_short _index);
    void setDrawType(DRAWTYPE _drawtype);
    void setRotation(u_short _index, QMatrix4x4 _rotation);
    void setMove(u_short _index, QMatrix4x4 _move);
    void setCordi(vector2f  _x, vector2f _y, vector2f _z);
    void setRender();
private:
//    QMatrix4x4 m_rotation = {
//        1, 0, 0, 0,
//        0, 1, 0, 0,
//        0, 0, 1, 0,
//        0, 0, 0, 1
//    };
    u_short m_curIndex = 0;
    CVaoVboManager* m_vaovboManager;
    QGLWidget*  m_glwidget;
    map<u_short, CRender*>                      m_therenders;
    map<u_short, GLuint>						m_uniformIndexChoosePntAnixGrids;
    map<u_short, GLuint>						m_uniformIndexRotPntAnixGrids;
    map<u_short, GLuint>						m_uniformIndexMovePntAnixGrids;
    map<u_short, GLuint>						m_uniformIndexProjectionPntAnixGrids;
    map<u_short, GLuint>                        m_uniformIndexDrawtypePntAnixGrids;
    map<u_short, QMatrix4x4>                    m_rotations;
    map<u_short, QMatrix4x4>                    m_moves;
    map<u_short, DRAWTYPE>                      m_drawtypes;

    CAxis* m_axis = nullptr;

};

#endif // CAXISMANAGER_H
