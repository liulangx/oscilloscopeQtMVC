#ifndef CGRAPHICSVIEW_H
#define CGRAPHICSVIEW_H
#include <QGraphicsView>
#include <QResizeEvent>
#include <QMatrix4x4>

//控制层control
class CGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    CGraphicsView(QWidget* _parent = nullptr);

signals:
//    void rotationChanged(QMatrix4x4 _rotation);

protected:
    void resizeEvent(QResizeEvent *event) override;


//    //响应鼠标动作，实现旋转功能
//    void mousePressEvent(QMouseEvent *event);
//    void mouseMoveEvent(QMouseEvent *event);
//    void mouseReleaseEvent(QMouseEvent *event);
//    void setRot(float _x, float _y);
//    QMatrix4x4          m_rotation = {
//                                1, 0, 0, 0,
//                                0, 1, 0, 0,
//                                0, 0, 1, 0,
//                                0, 0, 0, 1
//                            };

//    bool	m_leftPushDown = false;		//左键按下
//    bool	m_rightPushDown = false;	//右键按下
//    int		m_mouseCordx = 0;			//左键鼠标位置x
//    int		m_mouseCordy = 0;			//左键鼠标位置y
//    u_char  m_frameType = 0;

};

#endif // CGRAPHICSVIEW_H
