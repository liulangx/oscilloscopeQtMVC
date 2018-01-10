#ifndef CLINES_H
#define CLINES_H
#include "Database.h"
#include "DataManage/CVaoVboManager.h"
#include "AxisAndGrid/CGrid.h"
#include "Shaders/CRender.h"
#include "tools.h"
#include <QGLShader>
#include <QGLShaderProgram>
#include <QMessageBox>
#include <QOpenGLFunctions_4_3_Core>
#include <map>
using std::map;
class CSceneManager;

class CLines : public QObject, public QOpenGLFunctions_4_3_Core
{
    Q_OBJECT
public:
    enum Attribute
    {
        LINE_POSITION,
        LINE_COLOUR,
        LINE_INDEX
    };

    enum DRAWTYPE {
        XZY = 0,
        XY,
        XZ,
        YZ
    };

    explicit CLines(QObject* _lineManager, u_short _imgIndex, CVaoVboManager* _vaovboManager, QGLWidget* _widget);
    ~CLines();

    void cleanUp();
    void initial();
    void initialRender();
    void createNewLineForSameImg(size_t _lineIndex, size_t _pointSize);
    //setRenderParam 在initial执行后立刻调用，为了能在draw阶段使用geometry shader
    void setRenderParam(GLuint _uniformIndexXyPlaneMarkForLines, GLuint _uniformIndexXzPlaneMarkForLines, GLuint _uniformIndexYzPlaneMarkForLines, GLuint _uniformIndexXLowerForLines, GLuint _uniformIndexYLowerForLines, GLuint _uniformIndexZLowerForLines); //// deprecated!
    void draw();
    void clearUp();
    void setColor(size_t _lineIndex, vector4f _color);
    vector4f getColor(size_t _lineIndex) const;
//    void addLine(const vector3f& _posion, GLfloat _xLower, GLfloat _yLower, GLfloat _zLower);
    bool addPoint(size_t _lineindex, const vector3f& _position);
    size_t addLine(size_t _lineIndex, size_t _pointSize);
    void addPoint(size_t _lineIndex, const vector3f & _position, GLfloat _xLower, GLfloat _yLower, GLfloat _zLower);

    void setRotation(QMatrix4x4 _rotation);
    void setMove(QMatrix4x4 _move);
    void setZoom(float _scale);
    void setDrawtype(CGrid::DRAWTYPE _drawtype);
    void setRender();

    void setDraw();
    void setXYPlaneOn();
    void setXZPlaneOn();
    void setYZPlaneOn();
signals:
    void adjustGridNumer(u_short _imgIndex, vector2f _xrange, vector2f _yrange, vector2f _zrange, CGrid::RangeChange _xRanChange, CGrid::RangeChange _yRanChange, CGrid::RangeChange _zRanChange);
private:
    GLboolean xyMarks = true;
    GLboolean xzMarks = true;
    GLboolean yzMarks = true;
    map<size_t, GLuint> m_vaos;
    map<size_t, vector4f> m_colors/* = {1, 0, 0, 1}*/;
    map<size_t, GLuint> m_vbos;
    map<size_t, size_t> m_pointCounts /*= 0*/;
    map<size_t, size_t> m_pointSizes;
    size_t m_persize;

    vector4f m_lineColor = {1.0f, 0.0f, 0.0f, 1.0f};
    float m_zoom = 1;
    vector2f m_xRange = {1, 0};
    vector2f m_yRange = {1, 0};
    vector2f m_zRange = {1, 0};
    GLboolean m_first2Two = false;

    DRAWTYPE m_drawtype = DRAWTYPE::XZY;

//    map<u_short, CGrid::RangeChange> m_xRanChanges/* = CGrid::RangeChange::NotChange*/;
//    map<u_short, CGrid::RangeChange> m_yRanChanges/* = CGrid::RangeChange::NotChange*/;
//    map<u_short, CGrid::RangeChange> m_zRanChanges/* = CGrid::RangeChange::NotChange*/;

    QMatrix4x4 m_move = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
    QMatrix4x4 m_projection = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
    QMatrix4x4 m_rotation = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };

    //线段在三个方向上的分量
    GLfloat m_xLower = 0.0f;
    GLfloat m_yLower = 0.0f;
    GLfloat m_zLower = 0.0f;

    GLboolean m_XYPlaneOn = false;
    GLboolean m_XZPlaneOn = false;
    GLboolean m_YZPlaneOn = false;

    GLuint m_uniformIndexXyPlaneMarkForLines;
    GLuint m_uniformIndexXzPlaneMarkForLines;
    GLuint m_uniformIndexYzPlaneMarkForLines;

    GLuint m_uniformIndexXLowerForLines;
    GLuint m_uniformIndexYLowerForLines;
    GLuint m_uniformIndexZLowerForLines;


    GLuint m_uniformIndexChosePntAnixGridForLines;
    GLuint m_uniformIndexRangeXPntAnixGridForLines;
    GLuint m_uniformIndexRangeYPntAnixGridForLines;
    GLuint m_uniformIndexRangeZPntAnixGridForLines;
    GLuint m_uniformIndexScalePntAnixGridForLines;
    GLuint m_uniformIndexRotPntAnixGridForLines;
    GLuint m_uniformIndexMovePntAnixGridForLines;
    GLuint m_uniformIndexBasecordPntAnixGridForLines;
    GLuint m_uniformIndexDrawtypePntAnixGridForLines;
    GLuint m_uniformIndexProjectionPntAnixGridForLines;
    GLuint m_uniformIndexViewLinefactorPntAnixGridForLines;
    GLuint m_uniformIndexLineColorPntAnixGridForLines;
    //size_t						m_draws = 0;			//已经画了的点
    QGLWidget*                  m_glwidget;
    GLfloat                     m_zeroGate = 0.00000001f;

    bool						m_stateChange = true;		//????????
    bool                        m_RangeChange = false;
    CGrid::RangeChange  m_xRanChange = CGrid::RangeChange::NotChange;
    CGrid::RangeChange  m_yRanChange = CGrid::RangeChange::NotChange;
    CGrid::RangeChange  m_zRanChange = CGrid::RangeChange::NotChange;

    CVaoVboManager* m_vaovboManager = nullptr;
    CRender* m_lineRender = nullptr;
    u_short m_imgIndex = 0;
};

#endif // CLINES_H
