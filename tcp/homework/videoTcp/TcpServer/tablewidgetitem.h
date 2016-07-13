#ifndef TABLEWIDGWTITEM_H
#define TABLEWIDGWTITEM_H

#include <QTableWidgetItem>

class TableWidgetItem : public QTableWidgetItem
{
public:
    TableWidgetItem(const QIcon &icon1, const QIcon&icon2,const QString &name);
    ~TableWidgetItem();
    QTableWidgetItem* getNameItem()const {return dev;}
    QString getDevName()const {return dev_name;}
    void workStates_slots(int s);
private:

    QIcon stop_Icon;
    QIcon work_Icon;

    QString dev_name;

    QTableWidgetItem *dev;
};

#endif // TABLEWIDGWTITEM_H
