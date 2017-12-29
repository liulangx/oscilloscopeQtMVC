#ifndef CMVCWIDGET_H
#define CMVCWIDGET_H
#include "MVC/CScene.h"
#include "MVC/CGraphicsView.h"
#include <QGLWidget>
#include <QWidget>
#include <QRect>

class CMVCWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CMVCWidget(QRect _initWindowForView, QWidget* parent = nullptr); //推荐使用
    explicit CMVCWidget(QWidget* parent = 0);   //默认函数


    void initGL();
    void update();
signals:
//    void rotationChanged(QMatrix4x4 _rotation); //给模型层发送旋转矩阵改变的信号
public slots:
//    void onRotationChanged(QMatrix4x4 _rotation); // 接受从控制层发送来的旋转矩阵改变信号,将矩阵传给模型层（rotationChanged）
private:
    QRect           m_initWindowForView;
    CScene*         m_scene;        //管理数据      模型层model
    CGraphicsView*  m_graphicsView; //管理用户交互    控制层control
    QGLWidget*      m_glWidget;     //管理视图      视图层view
    QHBoxLayout     m_layout;

};

#endif // CMVCWIDGET_H
