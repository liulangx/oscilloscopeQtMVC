#include "LLComboWidget.h"
#include "DataManage/CVaoVboManager.h"
#include "mainwindow.h"
#include <QHBoxLayout>
#include <QGridLayout>


int main(int argc, char **argv)
{
//    QApplication app(argc, argv);
//    QRect initWindowForView(0, 0, 1024, 768);
//    LLComboWidget widget;
//    for(u_short i(0); i < 1; ++i)
//    {
//        widget.createNewMVCWidget(i);
//    }
//    widget.show();

//    return app.exec();

    QApplication app(argc, argv);

    MainWindow w;
    w.setWindowTitle("飞行器数据可视化平台");
    w.show();
    w.showMaximized();
    w.showMinimized();
    app.connect(&app, SIGNAL(lastWindowClosed()), &app, SLOT(quit()));
    return app.exec();
}

