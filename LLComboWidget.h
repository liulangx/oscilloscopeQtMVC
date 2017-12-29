#ifndef LLCOMBOWIDGET_H
#define LLCOMBOWIDGET_H
#include "MVC/CMVCWidget.h"
#include "Database.h"

#include <map>
#include <QWidget>
#include <QRect>
#include <QGridLayout>
#include <QTimer>

using namespace std;

class LLComboWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LLComboWidget(QRect _initWindowForView, QWidget *parent = nullptr);
    explicit LLComboWidget(QWidget *parent = nullptr);
    ~LLComboWidget();
    void createNewMVCWidget(u_short _index);
signals:
    void newMVCWidget(u_short _index);
public slots:
    void onNewMVCWidget(u_short _index);
    void update();
private:
    QTimer m_timer;
    QRect m_initWindowForView;//(0, 0, 1024, 768);
    map<u_short, CMVCWidget*> m_mvcWidgets;
    QGridLayout         m_qGridLayout;
};

#endif // LLCOMBOWIDGET_H
