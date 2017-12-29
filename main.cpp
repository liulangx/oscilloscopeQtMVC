//#include "CScene.h"

//#include "CGraphicsView.h"
#include "MVC/CMVCWidget.h"
#include "LLComboWidget.h"
#include "DataManage/CVaoVboManager.h"
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
    widget.show();



    return app.exec();
}

