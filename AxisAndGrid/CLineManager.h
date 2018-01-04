#ifndef CLINEMANAGER_H
#define CLINEMANAGER_H
#include "CLines.h"
#include <QOpenGLFunctions_4_3_Core>
#include <vector>
#include <QtMath>
#include <QGLWidget>
#include <map>
class CSceneManager;

using std::map;

class CLineManager : public QObject, public QOpenGLFunctions_4_3_Core
{
    Q_OBJECT
public:
    enum DRAWTYPE {
        XZY = 0,
        XY,
        XZ,
        YZ
    };
    explicit CLineManager(QObject* _sceneManger, CVaoVboManager* _vaovboManager, QGLWidget* _widget);
    ~CLineManager();
    void cleanUp();
    void initial();
    void createNewLineForNewIndex(u_short _imgIndex);
    bool addPoint(u_short _imgIndex, size_t _lineindex, const vector3f & _position);
//    void setDraw(u_short _imgIndex);
    void draw();
    void setCurIndex(u_short _curIndex);
    void setRotation(u_short _imgIndex, QMatrix4x4 _rotation);
    void setMove(u_short _imgIndex, QMatrix4x4 _move);
    void setZoom(float _scale);
    void setDrawtype(CGrid::DRAWTYPE _drawtype);
    void setRender();
private:
    u_short                    m_curIndex = 0;
    CVaoVboManager*              m_vaovboManager;
    QGLWidget*                  m_glwidget;
//    CSceneManager*              m_sceneManger;

    map<u_short, CLines*>       m_mapIdx_Lines;


//    map<u_short, vector2f> m_xRanges;
//    map<u_short, vector2f> m_yRanges;
//    map<u_short, vector2f> m_zRanges;
//    map<u_short, QMatrix4x4> m_rotations;
//    map<u_short, QMatrix4x4> m_moves;
//    map<u_short, QMatrix4x4> m_projections;
//    map<u_short, float> m_zooms;
//    map<u_short, vector4f> m_lineColors;
//    map<u_short, DRAWTYPE> m_drawtypes;

};

#endif // CLINEMANAGER_H
