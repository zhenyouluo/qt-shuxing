#include "tablewidgetitem.h"
#include <QDebug>

TableWidgetItem::TableWidgetItem(const QIcon &icon1, const QIcon &icon2, const QString &name):
    QTableWidgetItem(icon1,name),
    stop_Icon(icon1),
    work_Icon(icon2),
    dev_name(name)
{
    setIcon(icon1);
    dev = new QTableWidgetItem("");
    dev->setTextAlignment(Qt::AlignVCenter|Qt::AlignLeft);
}
TableWidgetItem::~TableWidgetItem()
{
}
void TableWidgetItem::workStates_slots(int s)
{
    if (s > 0)
    {
        setIcon(work_Icon);
    }
    else
    {
        setIcon(stop_Icon);
    }
}
