#include "CInsQtWinManager.h"
#include "MVC/CScene.h"

CInsQtWinManager::CInsQtWinManager(CScene *_scene)
    : QObject(_scene)
{
//    //CGraphicsWidget * widgetP = new CGraphicsWidget;
//    ItemDialog* itemDialog = new ItemDialog;
////    widgetP->setCacheMode(QGraphicsItem::ItemCoordinateCache);
////    widgetP->setZValue(1e30);
////    widgetP->setWidget(itemDialog);
//    itemDialog->move(100, 160);
//    itemDialog->resize(itemDialog->sizeHint());
//    itemDialog->setWindowTitle("This is a test");
////    widgetP->setVisible(true);

//    ItemDialog* itemDialog1 = new ItemDialog;

//    CScene* scene = qobject_cast<CScene*>(this->parent());

//    CTwoSidedGraphicsWidget *twoSided = new CTwoSidedGraphicsWidget(scene);
//    twoSided->setWidget(0, itemDialog);
//    twoSided->setWidget(1, itemDialog1);
//    CTwoSidedGraphicsWidget *twoSided1 = new CTwoSidedGraphicsWidget(scene);


//    ItemDialog* itemDialog2 = new ItemDialog;
//    ItemDialog* itemDialog3 = new ItemDialog;
//    twoSided1->setWidget(0, itemDialog2);
//    twoSided1->setWidget(1, itemDialog3);
//    itemDialog2->move(300, 160);
//    itemDialog2->resize(itemDialog2->sizeHint());


//    connect(itemDialog, SIGNAL(doubleClicked()), twoSided, SLOT(flip()));
//    connect(itemDialog1, SIGNAL(doubleClicked()), twoSided, SLOT(flip()));
//    connect(itemDialog2, SIGNAL(doubleClicked()), twoSided1, SLOT(flip()));
//    connect(itemDialog3, SIGNAL(doubleClicked()), twoSided1, SLOT(flip()));
    //    this->addItem(widgetP);
}

CInsQtWinManager::~CInsQtWinManager()
{

}

void CInsQtWinManager::initGL(u_short _index)
{
    if(m_itemDialogs.find(_index) != m_itemDialogs.end())
    {
#ifdef DEBUG
        qWarning() << "该窗口管理器已经存在";
#endif
        return;
    }
    int xOffset = 10;
    int yOffset = 30;

    QString title = QString("图像 %1").arg(_index);
    ItemDialog* itemDialog = new ItemDialog(this, _index, title);
    itemDialog->setWindowTitle(title);
//    itemDialog->resize(itemDialog->sizeHint());

//    itemDialog->setWindowFlag(Qt::FramelessWindowHint);
//    itemDialog->setAttribute(Qt::WA_TranslucentBackground, true);

    if(!m_itemDialogs.empty())
    {
        map<u_short, ItemDialog*>::reverse_iterator it = m_itemDialogs.rbegin();
        ItemDialog* lastDialog = it->second;
        xOffset = lastDialog->x() + lastDialog->frameGeometry().width();/*geo.right();*/
        yOffset = lastDialog->y();

    }
    else
    {
//        xOffset = 0;
//        yOffset = itemDialog->geometry().y() - itemDialog->y();
//        QRect t = itemDialog->geometry();
//        QRect t2 = itemDialog->frameGeometry();
//        int a = 1;
    }
    itemDialog->move(xOffset, yOffset);


    CScene* scene = qobject_cast<CScene*>(this->parent());

    ItemDialog* itemDialog1 = new ItemDialog(this, _index, title);
    CTwoSidedGraphicsWidget *twoSided = new CTwoSidedGraphicsWidget(scene);
    twoSided->setWidget(0, itemDialog);
    twoSided->setWidget(1, itemDialog1);

    connect(itemDialog, SIGNAL(doubleClicked()), twoSided, SLOT(flip()));
    connect(itemDialog1, SIGNAL(doubleClicked()), twoSided, SLOT(flip()));

    m_itemDialogs.insert(std::pair<u_short, ItemDialog*>(_index, itemDialog));
    m_twoSidedGraWidgets.insert(std::pair<u_short, CTwoSidedGraphicsWidget*>(_index, twoSided));
}

