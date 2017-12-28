#include "CGraphicsView.h"
class CMVCWidget;

CGraphicsView::CGraphicsView(QWidget *_parent)
    : QGraphicsView(_parent)
{
    setWindowTitle(tr("Boxes"));
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    //setRenderHints(QPainter::SmoothPixmapTransform);
//    connect(this, SIGNAL(rotationChanged(QMatrix4x4)), _parent/*qobject_cast<CMVCWidget*>(this->parent())*/, SLOT(onRotationChanged(QMatrix4x4)));
}

void CGraphicsView::resizeEvent(QResizeEvent *event) {
    if (scene())
        scene()->setSceneRect(QRect(QPoint(0, 0), event->size()));
    QGraphicsView::resizeEvent(event);
}

//void CGraphicsView::mousePressEvent(QMouseEvent *event)
//{
//    QGraphicsView::mousePressEvent(event);
//    if(event->isAccepted())
//        return;
//    if (event->button() == Qt::LeftButton)
//    {
//        m_leftPushDown = true;
//        m_mouseCordx = event->x();
//        m_mouseCordy = event->y();
//    }
//    if (event->button() == Qt::RightButton)
//    {
//        m_rightPushDown = true;
//        m_mouseCordx = event->x();
//        m_mouseCordy = event->y();
//    }

//}

//void CGraphicsView::mouseMoveEvent(QMouseEvent *event)
//{
//    QGraphicsView::mouseMoveEvent(event);
////    if(event->isAccepted())
////        return;
//    if(0 == m_frameType)
//    {
//        if (m_leftPushDown)
//        {
//            float _roatx = m_mouseCordx - event->x();
//            float _roaty = m_mouseCordy - event->y();
//            m_mouseCordx = event->x();
//            m_mouseCordy = event->y();
//            setRot(_roaty / 200,  _roatx/ 200/*,0*/);
//        }

//    }
//}

//void CGraphicsView::mouseReleaseEvent(QMouseEvent *event)
//{
//    //这里有对鼠标动作的不当处理，在该步骤之前的鼠标事件处理中，有被处理过的鼠标Release事件的处理。
//    QGraphicsView::mouseReleaseEvent(event);
////    if(event->isAccepted())
////        return;
//    if (event->button() == Qt::LeftButton)
//    {
//        m_leftPushDown = false;
//    }
//    if (event->button() == Qt::RightButton)
//    {
//        m_rightPushDown = false;
//    }
//}

//void CGraphicsView::setRot(float _x, float _y)
//{
//    m_rotation = QMatrix4x4(1.0, 0.0, 0.0, 0.0,
//                    0.0, cos(_x), -sin(_x), 0.0,
//                    0.0, sin(_x), cos(_x), 0.0,
//                        0.0, 0.0, 0.0, 1.0)*
//        QMatrix4x4(cos(_y), 0.0, sin(_y), 0.0,
//            0.0, 1.0, 0.0, 0.0,
//            -sin(_y), 0.0, cos(_y), 0.0,
//            0.0, 0.0, 0.0, 1.0)/**
//                QMatrix4x4(cos(_z), -sin(_z), 0.0, 0.0,
//                    sin(_z), cos(_z), 0.0, 0.0,
//                    0.0, 0.0, 1.0, 0.0,
//                    0.0, 0.0, 0.0, 1.0)*/*m_rotation;
//    emit rotationChanged(m_rotation);
//    //update();
//}
