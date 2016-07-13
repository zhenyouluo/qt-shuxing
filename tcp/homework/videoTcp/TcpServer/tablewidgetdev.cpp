#include "tablewidgetdev.h"
#include <QAction>
#include <QHeaderView>
#include <QDebug>

#include "tablewidgetitem.h"
TableWidgetDEV::TableWidgetDEV(const QStringList &headNames, QWidget *parent) :
    QTableWidget(parent)
{
    setColumnCount(headNames.size());
    setHorizontalHeaderLabels(headNames);
    //horizontalHeader()->setResizeMode(0,QHeaderView::Stretch);
    //horizontalHeader()->setResizeMode(1,QHeaderView::Stretch);
    setShowGrid(false);

    setSelectionBehavior(QAbstractItemView::SelectRows);

    unloadDev = new QAction(tr("unload"),this);
    addAction(unloadDev);
    setContextMenuPolicy(Qt::ActionsContextMenu);
    connect(unloadDev,SIGNAL(triggered()),this,SLOT(dounload()));
}
void TableWidgetDEV::dounload()
{
    QTableWidgetItem *item = currentItem();
    if (item == NULL)
    {
        return;
    }
    emit unload_signals(item->data(0).toString());
}
void TableWidgetDEV::clearItem(const QString &no)
{
    QList<QTableWidgetItem*> temp = findItems(no,Qt::MatchCaseSensitive);
    foreach(const QTableWidgetItem* c ,temp)
    {
        removeRow(row(c));
    }
}
void TableWidgetDEV::addItems(TableWidgetItem *item)
{
    int r = rowCount();
    insertRow(r);
    setItem(r,0,item);
    setItem(r,1,item->getNameItem());
}
void TableWidgetDEV::workState_slots(const QString &dename, int s)
{
    QList<QTableWidgetItem*> temp = findItems(dename,Qt::MatchCaseSensitive);
    foreach(QTableWidgetItem* c ,temp)
    {
        static_cast<TableWidgetItem*>(c)->workStates_slots(s);
    }

}
