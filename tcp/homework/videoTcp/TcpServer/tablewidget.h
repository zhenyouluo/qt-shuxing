#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QTableWidget>
#include <QStandardItem>

class QAction;
class QMenu;

class TableWidget : public QTableWidget
{
    Q_OBJECT
public:
    explicit TableWidget(const QStringList &headNames = QStringList(), QWidget *parent = 0);
    ~TableWidget(){}
    void addItems(const QList<QTableWidgetItem *> &list);
signals:
    void kill_signals(const QString &no);
    void showInfo_signals(const QString &no);
public slots:
    void clearItem(const QString &no);
protected slots:
    void doKillIt();
    void doShowInfo();
private:
    QAction *killIt;
    QAction *showInfo;

    void initUI();
    
};

#endif // TABLEWIDGET_H
