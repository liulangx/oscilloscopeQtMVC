#include "InsertQtWin/ItemDialog.h"


ItemDialog::ItemDialog()
    : QDialog(0, Qt::CustomizeWindowHint | Qt::WindowTitleHint)
{
    setWindowTitle(tr("Items (double click to flip)"));
    setWindowOpacity(0.75);
    resize(160, 100);

    QVBoxLayout *layout = new QVBoxLayout;
    setLayout(layout);
    QPushButton *button;

    button = new QPushButton(tr("Add Qt box"));
    layout->addWidget(button);
    connect(button, SIGNAL(clicked()), this, SLOT(triggerNewQtBox()));

    button = new QPushButton(tr("Add circle"));
    layout->addWidget(button);
    connect(button, SIGNAL(clicked()), this, SLOT(triggerNewCircleItem()));

    button = new QPushButton(tr("Add square"));
    layout->addWidget(button);
    connect(button, SIGNAL(clicked()), this, SLOT(triggerNewSquareItem()));

    layout->addStretch(1);

}

void ItemDialog::triggerNewQtBox()
{

}

void ItemDialog::triggerNewCircleItem()
{

}

void ItemDialog::triggerNewSquareItem()
{

}

void ItemDialog::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        emit doubleClicked();
}
