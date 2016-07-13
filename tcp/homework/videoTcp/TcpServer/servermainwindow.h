#ifndef SERVERMAINWINDOW_H
#define SERVERMAINWINDOW_H

#include <QMainWindow>
#include <QLayout>
#include <QMap>
#include "LogInfo.h"
#include <QTableWidget>

class QAction;
class QMenu;
class QToolBar;
class TableWidget;
class TableWidgetDEV;
class CameraServer;


namespace Ui {
class ServerMainWindow;
}

class ServerMainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit ServerMainWindow(QWidget *parent = 0);
    ~ServerMainWindow();
signals:
    void clientInfoUpdataOK_signals(int id,const QString& info);
    void devInfoUpdataOK_signals(const QString&name,const QString&info);
    void devWorkState_signals(bool s);
public slots:
    void showStateInfo(const QString &message);
protected:
    void closeEvent(QCloseEvent *e);
protected slots:
    void showLog_slots();

    void getClientThreadInfo_slots(const QStringList& list);
    void getDevThreadInfo_slots(const QStringList& list);
    void updateUI_devName(const QString& name);
    void updataUI_devThread(const QString& name);
    void updataUI_clientThread(int id);
    void updataUI_devThreadNum(const QString &name, int i);

    void updataUI_clientThreadDevName(int id,const QString &name);

    void start_server();
    void stop_server();

    void recordLogInfo_slots(int id);

private:
    Ui::ServerMainWindow *ui;

    CameraServer *server;

    QToolBar *toolBar;
    TableWidget *clientThreadTable;
    TableWidget *devTable;

    TableWidgetDEV *devNameTable;

    QHBoxLayout *layout0;
    QHBoxLayout *layout1;
    QHBoxLayout *layout2;

    QVBoxLayout *layout3;
    QGridLayout *layout4;



    QAction *startAction;//打开服务器
    QAction *stopAction;//关闭服务器
    QAction *quit;
    QAction *killThread;//杀死线程
    QAction *showLog;//查看日志
    QAction *settleLog;//整理日志
    QAction *helpAction;

    QMenu *fileMenu;
    QMenu *logMenu;
    QMenu *helpMenu;

    QMap<int,LogMessage> logmap;

    void initUI();
    void connects();
    void initUI_devNameTable();
    void clearTableWidget(QTableWidget *t);
    void updataUI();
    QString QTableWidgetItemsToQString(const QList<QTableWidgetItem*> &list);
    QList<QTableWidgetItem*> rowItems(QTableWidget* t,int r);



};

#endif // SERVERMAINWINDOW_H
