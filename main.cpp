//#include "CScene.h"

//#include "CGraphicsView.h"
#include "MVC/CMVCWidget.h"
#include "LLComboWidget.h"
#include <map>
#include <QtWidgets>
#include <QGLWidget>
#include <QHBoxLayout>
#include <QGridLayout>


int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QRect initWindowForView(0, 0, 1024, 768);
    LLComboWidget widget;
    for(u_short i(0); i < 1; ++i)
    {
        widget.createNewMVCWidget(i);
    }
//    u_short index = 0;
//    widget.createNewMVCWidget(index);
    widget.show();
//    CMVCWidget* mvcWidget1 = new CMVCWidget(initWindowForView);
////    mvcWidget1->show();
////    mvcWidget1->initGL();
//    CMVCWidget* mvcWidget2 = new CMVCWidget(initWindowForView);
//    CMVCWidget* mvcWidget3 = new CMVCWidget(initWindowForView);
//    CMVCWidget* mvcWidget4 = new CMVCWidget(initWindowForView);
////    mvcWidget2->initGL();
//    QWidget widget;
//    QGridLayout* qGridLayout = new QGridLayout;
//    qGridLayout->addWidget(mvcWidget1, 0, 0);
//    qGridLayout->addWidget(mvcWidget2, 0, 1);
//    qGridLayout->addWidget(mvcWidget3, 1, 0);
//    qGridLayout->addWidget(mvcWidget4, 1, 1);
//    widget.setGeometry(initWindowForView);
//    widget.setLayout(qGridLayout);
//    widget.show();


    return app.exec();
}

