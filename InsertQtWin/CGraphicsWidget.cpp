#include "InsertQtWin/CGraphicsWidget.h"

CGraphicsWidget::CGraphicsWidget()
    : QGraphicsProxyWidget(0, Qt::Window)
{

}

QVariant CGraphicsWidget::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange && scene()) {
        QRectF rect = boundingRect();
        QPointF pos = value.toPointF();
        QRectF sceneRect = scene()->sceneRect();
        if (pos.x() + rect.left() < sceneRect.left())
            pos.setX(sceneRect.left() - rect.left());
        else if (pos.x() + rect.right() >= sceneRect.right())
            pos.setX(sceneRect.right() - rect.right());
        if (pos.y() + rect.top() < sceneRect.top())
            pos.setY(sceneRect.top() - rect.top());
        else if (pos.y() + rect.bottom() >= sceneRect.bottom())
            pos.setY(sceneRect.bottom() - rect.bottom());
        return pos;
    }
    return QGraphicsProxyWidget::itemChange(change, value);
}

void CGraphicsWidget::resizeEvent(QGraphicsSceneResizeEvent *event)
{
    setCacheMode(QGraphicsItem::NoCache);
    setCacheMode(QGraphicsItem::ItemCoordinateCache);
    QGraphicsProxyWidget::resizeEvent(event);
}

void CGraphicsWidget::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing, false);
    QGraphicsProxyWidget::paint(painter, option, widget);
    //painter->setRenderHint(QPainter::Antialiasing, true);
}
