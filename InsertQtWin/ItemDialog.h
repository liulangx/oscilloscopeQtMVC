#ifndef ITEMDIALOG_H
#define ITEMDIALOG_H
#include <QDialog>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMouseEvent>

class ItemDialog : public QDialog
{
    Q_OBJECT
public:
    enum ItemType {
        QtBoxItem,
        CircleItem,
        SquareItem,
    };

    ItemDialog();
public slots:
    void triggerNewQtBox();
    void triggerNewCircleItem();
    void triggerNewSquareItem();
signals:
    void doubleClicked();
    void newItemTriggered(ItemDialog::ItemType type);
protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;
};

#endif // ITEMDIALOG_H
