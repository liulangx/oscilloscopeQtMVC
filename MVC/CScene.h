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
#include "AxisAndGrid/CSceneManager.h"
#include "InsertQtWin/CInsQtWinManager.h"

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
    void cleanUp();
    void drawBackground(QPainter *painter, const QRectF &rect) override;
    void initGL(u_short _index);
    bool addPoint(u_short _imgIndex, size_t _lineindex, const vector3f &_position);
    void setColor(u_short _imgIndex, size_t _lineIndex, vector4f _color);
public slots:
//    void onRotationChanged(QMatrix4x4 _rotation);
    void onNewItemTriggered(ItemDialog::ItemType _type, u_short _index);
private:
    QGLWidget* m_widget;

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void wheelEvent(QGraphicsSceneWheelEvent *event);

    CSceneManager* m_sceneManager;
    CInsQtWinManager* m_insQtWinManager;
};

//#endif
