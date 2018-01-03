#include "LLComboWidget.h"
#include "DataManage/CVaoVboManager.h"
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

