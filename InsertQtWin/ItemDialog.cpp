#include "InsertQtWin/ItemDialog.h"
#include "CInsQtWinManager.h"
#include "MVC/CScene.h"

ItemDialog::ItemDialog(CInsQtWinManager *_insQtWinManager, u_short _index, QString _title)
    : m_insQtWinManager(_insQtWinManager)
    , QDialog(0, Qt::CustomizeWindowHint | Qt::WindowTitleHint)
    , m_index(_index)
{
//    startTimer(500);
    //setWindowTitle(tr("Items (double click to flip)"));
    setWindowOpacity(0.75);
//    setWindowFlags(Qt::FramelessWindowHint);
//    resize(160, 100);

    m_girdLayout = new QGridLayout;
    m_hlayout1 = new QHBoxLayout;
    m_hlayout2 = new QHBoxLayout;
    setLayout(m_girdLayout);
    m_label = new QLabel(_title);
    m_label->setAlignment(Qt::AlignHCenter);
    m_girdLayout->addWidget(m_label, 0, 0);
//    layout->setAlignment(Qt::AlignHCenter);

    m_buttonMakeCur = new QPushButton(tr("显示"));
    m_girdLayout->addWidget(m_buttonMakeCur, 1, 0, Qt::AlignHCenter);
    QObject::connect(m_buttonMakeCur, SIGNAL(clicked(bool)), this, SLOT(triggerMakeCurrent()));

    m_buttonGrid = new QCheckBox(tr("网格"));
    m_hlayout1->addWidget(m_buttonGrid);
    QObject::connect(m_buttonGrid, SIGNAL(stateChanged(int)), this, SLOT(triggerHoVGrid()));

    m_buttonAxis = new QCheckBox(tr("坐标"));
    m_hlayout1->addWidget(m_buttonAxis);
    QObject::connect(m_buttonAxis, SIGNAL(stateChanged(int)), this, SLOT(triggerHoVAxis()));

    m_girdLayout->addLayout(m_hlayout1, 2, 0);
    m_hlayout1->setAlignment(Qt::AlignHCenter);

    m_buttonXY = new QCheckBox(tr("XY"));
    m_hlayout2->addWidget(m_buttonXY);
    QObject::connect(m_buttonXY, SIGNAL(stateChanged(int)), this, SLOT(triggerHoVXY()));

    m_buttonXZ = new QCheckBox(tr("XZ"));
    m_hlayout2->addWidget(m_buttonXZ);
    QObject::connect(m_buttonXZ, SIGNAL(stateChanged(int)), this, SLOT(triggerHoVXZ()));

    m_buttonYZ = new QCheckBox(tr("YZ"));
    m_hlayout2->addWidget(m_buttonYZ);
    QObject::connect(m_buttonYZ, SIGNAL(stateChanged(int)), this, SLOT(triggerHoVYZ()));

    m_girdLayout->addLayout(m_hlayout2, 3, 0);
    m_hlayout2->setAlignment(Qt::AlignHCenter);
//    m_girdLayout->addStretch(1);

    QObject::connect(this, SIGNAL(newItemTriggered(ItemDialog::ItemType,u_short)), qobject_cast<CScene*>(m_insQtWinManager->parent()), SLOT(onNewItemTriggered(ItemDialog::ItemType, u_short)));

}

ItemDialog::~ItemDialog()
{
    this->cleanUp();
}

void ItemDialog::triggerMakeCurrent()
{
    emit newItemTriggered(ItemType::MakeCurrent, m_index);
}

void ItemDialog::triggerHoVGrid()
{
    emit newItemTriggered(ItemType::HoVGrid, m_index);
}

void ItemDialog::triggerHoVAxis()
{
    emit newItemTriggered(ItemType::HoVAxis, m_index);
}

void ItemDialog::triggerHoVXY()
{
    emit newItemTriggered(ItemType::HoVXY, m_index);
}

void ItemDialog::triggerHoVXZ()
{
    emit newItemTriggered(ItemType::HoVXZ, m_index);
}

void ItemDialog::triggerHoVYZ()
{
    emit newItemTriggered(ItemType::HoVYZ, m_index);
}


void ItemDialog::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        emit doubleClicked();
}

void ItemDialog::timerEvent(QTimerEvent *e)
{
    qDebug() << geometry().height() << frameGeometry().height();
}

void ItemDialog::cleanUp()
{
    delete m_label;
    delete m_buttonAxis;
    delete m_buttonGrid;
    delete m_buttonMakeCur;
    delete m_buttonXY;
    delete m_buttonXZ;
    delete m_buttonYZ;
    delete m_hlayout1;
    delete m_hlayout2;
    delete m_girdLayout;
}
