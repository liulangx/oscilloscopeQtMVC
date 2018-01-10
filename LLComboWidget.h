#ifndef LLCOMBOWIDGET_H
#define LLCOMBOWIDGET_H
#include "MVC/CMVCWidget.h"
#include "Database.h"
#include "UDPServer/CAsioAsyncServer.h"

#include <boost/thread/mutex.hpp>
#include <boost/thread.hpp>

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

    void recvMessage();
    void run();
    void closeTimer();
    void createNewMVCWidget(u_short _index);
signals:
    void newMVCWidget(u_short _index);
public slots:
    void onNewMVCWidget(u_short _index);
    void update();
private slots:
    void onTimeOut();
private:
    void readCirBufToCreateOpenGLImages();
    //boost circularBuffer类
    CirBufferLL             m_cirBuffer;
    //asio收发类
    CAsioAsyncServer*       m_server = nullptr;
    vector<u_short>         m_imageNumbers;

    QTimer m_timer;
    QRect m_initWindowForView;//(0, 0, 1024, 768);
    map<u_short, CMVCWidget*> m_mvcWidgets;
    CMVCWidget*          m_mvcWidget = nullptr;
    QGridLayout         m_qGridLayout;

//    QTimer          m_timer;
    boost::thread*  m_threadRecv = nullptr;
};

#endif // LLCOMBOWIDGET_H
