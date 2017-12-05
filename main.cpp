#include "scene.h"

#include <QtWidgets>
#include <QGLWidget>

class GraphicsView : public QGraphicsView
{
public:
    GraphicsView()
    {
        setWindowTitle(tr("Boxes"));
        setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
        //setRenderHints(QPainter::SmoothPixmapTransform);
    }

protected:
    void resizeEvent(QResizeEvent *event) override {
        if (scene())
            scene()->setSceneRect(QRect(QPoint(0, 0), event->size()));
        QGraphicsView::resizeEvent(event);
    }
};

class MyGLWidget : public QGLWidget
{
public:
    MyGLWidget(QWidget *parent = 0): QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
    {

    }
    void setScene(Scene* _scene)
    {
        m_scene = _scene;
    }

    ~MyGLWidget(){}
    QMatrix4x4          m_rotation = {
                                1, 0, 0, 0,
                                0, 1, 0, 0,
                                0, 0, 1, 0,
                                0, 0, 0, 1
                            };
private:
    Scene * m_scene;

    bool	m_leftPushDown = false;		//左键按下
    bool	m_rightPushDown = false;	//右键按下
    int		m_mouseCordx = 0;			//左键鼠标位置x
    int		m_mouseCordy = 0;			//左键鼠标位置y
    u_char m_frameType = 0;

    void setRot(float _x, float _y)
    {
        m_scene->setRot(_x, _y);
    }

    void mousePressEvent(QMouseEvent *event){
        if (event->button() == Qt::LeftButton)
        {
            m_leftPushDown = true;
            m_mouseCordx = event->x();
            m_mouseCordy = event->y();
        }
        if (event->button() == Qt::RightButton)
        {
            m_rightPushDown = true;
            m_mouseCordx = event->x();
            m_mouseCordy = event->y();
        }
    }

    void mouseMoveEvent(QMouseEvent *event)
    {
        if(0 == m_frameType)
        {
            if (m_leftPushDown)
            {
                float _roatx = m_mouseCordx - event->x();
                float _roaty = m_mouseCordy - event->y();
                m_mouseCordx = event->x();
                m_mouseCordy = event->y();
                setRot(_roaty / 200,  _roatx/ 200/*,0*/);
            }
        }
    }

    void mouseReleaseEvent(QMouseEvent *event)
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

};

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    int maxTextureSize = 1024;

    //QGLWidget *widget = new QGLWidget(QGLFormat(QGL::SampleBuffers));
    MyGLWidget *widget = new MyGLWidget();
    //QOpenGLWidget *widget = new QOpenGLWidget();
    Scene scene(1024, 768, maxTextureSize, widget);
    widget->setScene(&scene);
    widget->makeCurrent(); // The current context must be set before calling Scene's constructor



    GraphicsView view;
    view.setViewport(widget);
    view.setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    view.setScene(&scene);
    view.show();
    //QThread::sleep(10);
    scene.initGL();
    return app.exec();
}

