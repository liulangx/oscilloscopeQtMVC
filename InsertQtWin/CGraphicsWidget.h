#ifndef CGRAPHICSWIDGET_H
#define CGRAPHICSWIDGET_H
#include <QGraphicsProxyWidget>
#include <QGraphicsScene>
#include <QPainter>

class CGraphicsWidget : public QGraphicsProxyWidget
{
public:
    CGraphicsWidget();
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void resizeEvent(QGraphicsSceneResizeEvent *event) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // CGRAPHICSWIDGET_H
