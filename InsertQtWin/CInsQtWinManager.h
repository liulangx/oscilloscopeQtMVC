#ifndef CINSQTWINMANAGER_H
#define CINSQTWINMANAGER_H
#include "InsertQtWin/CTwoSidedGraphicsWidget.h"
#include "InsertQtWin/CGraphicsWidget.h"
#include "InsertQtWin/ItemDialog.h"
#include <map>
using std::map;
class CScene;

class CInsQtWinManager : public QObject
{
    Q_OBJECT
public:
    /*explicit */CInsQtWinManager(CScene* _scene);
    ~CInsQtWinManager();
    void cleanUp();
    void initGL(u_short _index);
private:
    map<u_short, ItemDialog*> m_itemDialogs;
    map<u_short, CTwoSidedGraphicsWidget*> m_twoSidedGraWidgets;

};

#endif // CINSQTWINMANAGER_H
