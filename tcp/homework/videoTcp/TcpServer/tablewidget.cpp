#include "tablewidget.h"

#include <QAction>
#include <QMenu>
#include <QHeaderView>
#include <QDebug>

TableWidget::TableWidget(const QStringList &headNames, QWidget *parent) :
    QTableWidget(parent)
{
    setColumnCount(headNames.size());
    setHorizontalHeaderLabels(headNames);
    for (int i = 0;i < headNames.size();++i)
    {
        //horizontalHeader()->setResizeMode(i,QHeaderView::Stretch);
    }
    setShowGrid(false);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    initUI();
    connect(killIt,SIGNAL(triggered()),this,SLOT(doKillIt()));
    connect(showInfo,SIGNAL(triggered()),this,SLOT(doShowInfo()));

}
void TableWidget::initUI()
{
    killIt = new QAction(tr("killIt"),this);
    showInfo = new QAction(tr("showInfo"),this);
    addAction(killIt);
    addAction(showInfo);
    setContextMenuPolicy(Qt::ActionsContextMenu);
}

void TableWidget::doKillIt()
{
    QTableWidgetItem *item = currentItem();
    if (item == NULL) return;
    emit kill_signals(item->data(0).toString());

}
void TableWidget::doShowInfo()
{
    QTableWidgetItem *item = currentItem();
    if (item == NULL)
    {
        //        qDebug()<<"~~";
        return;
    }
    emit showInfo_signals(item->data(0).toString());
}
void TableWidget::clearItem(const QString &no)
{
    QList<QTableWidgetItem*> temp = findItems(no,Qt::MatchCaseSensitive);
    foreach(const QTableWidgetItem* c ,temp)
    {
        removeRow(row(c));
    }

}
void TableWidget::addItems(const QList<QTableWidgetItem *> &list)
{
    int r = rowCount();
    insertRow(r);
    for (int i = 0;i < list.size();++i) {
        setItem(r,i,list.at(i));
    }
}
