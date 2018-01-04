#ifndef ITEMDIALOG_H
#define ITEMDIALOG_H
#include <QDialog>
#include <QLabel>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QPushButton>
#include <QMouseEvent>
#include <QDebug>
class CInsQtWinManager;
class CScene;

class ItemDialog : public QDialog
{
    Q_OBJECT
public:
    enum ItemType {
        MakeCurrent,
        HoVGrid,
        HoVAxis,
        HoVXY,
        HoVXZ,
        HoVYZ
    };

    explicit ItemDialog(CInsQtWinManager* _insQtWinManager, u_short _index, QString _title);
    ~ItemDialog();
public slots:
    void triggerMakeCurrent();
    void triggerHoVGrid();
    void triggerHoVAxis();
    void triggerHoVXY();
    void triggerHoVXZ();
    void triggerHoVYZ();
signals:
    void doubleClicked();
    void newItemTriggered(ItemDialog::ItemType _type, u_short _index);
protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void timerEvent(QTimerEvent *e) override;

    void cleanUp();

    u_short m_index;
    QGridLayout* m_girdLayout;
    QHBoxLayout* m_hlayout1;
    QHBoxLayout* m_hlayout2;
    QLabel* m_label;
    QPushButton* m_buttonMakeCur;
    QCheckBox* m_buttonGrid;
    QCheckBox* m_buttonAxis;
    QCheckBox* m_buttonXY;
    QCheckBox* m_buttonXZ;
    QCheckBox* m_buttonYZ;

    CInsQtWinManager* m_insQtWinManager;
};

#endif // ITEMDIALOG_H
