#ifndef TABLEWIDGETDEV_H
#define TABLEWIDGETDEV_H

#include <QTableWidget>
class TableWidgetItem;

class TableWidgetDEV : public QTableWidget
{
    Q_OBJECT
public:
    explicit TableWidgetDEV(const QStringList &headNames = QStringList(),QWidget *parent = 0);
    void addItems(TableWidgetItem *item);
    void workState_slots(const QString& dename,int s);
signals:
    void unload_signals(const QString &no);
public slots:
    void clearItem(const QString &no);    
protected slots:
    void dounload();
private:
    QAction *unloadDev;
    
};

#endif // TABLEWIDGETDEV_H
