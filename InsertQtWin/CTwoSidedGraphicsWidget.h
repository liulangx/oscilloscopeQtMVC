#ifndef CTWOSIDEDGRAPHICSWIDGET_H
#define CTWOSIDEDGRAPHICSWIDGET_H

#include "InsertQtWin/CGraphicsWidget.h"
#include <QTimer>
#include <QObject>
#include <QGraphicsScene>
class CTwoSidedGraphicsWidget : public QObject
{
    Q_OBJECT
public:
    CTwoSidedGraphicsWidget(QGraphicsScene *scene);
    void setWidget(int index, QWidget *widget);
    QWidget *widget(int index);
public slots:
    void flip();
protected slots:
    void animateFlip();
private:
    CGraphicsWidget *m_proxyWidgets[2];
    int m_current;
    int m_angle; // angle in degrees
    int m_delta;
};

#endif // CTWOSIDEDGRAPHICSWIDGET_H
