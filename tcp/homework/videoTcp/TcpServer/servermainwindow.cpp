#include "servermainwindow.h"
#include "ui_servermainwindow.h"

#include "tablewidget.h"
#include "showlog.h"
#include "tablewidgetdev.h"
#include "tablewidgetitem.h"
#include "cameraServer.h"

#include <QDir>
#include <QToolBar>
#include <QCloseEvent>
#include <QDebug>

ServerMainWindow::ServerMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ServerMainWindow),
    server(NULL)
{
    ui->setupUi(this);
    initUI();
    connects();
}

ServerMainWindow::~ServerMainWindow()
{
    delete ui;
}
void ServerMainWindow::closeEvent(QCloseEvent *e)
{
    if (server != NULL)
    {
        if (server->isListening())
        {
            e->ignore();
            QMessageBox::warning(this,QObject::trUtf8("警告！"),QObject::trUtf8("服务器正在运行中"));
        }
    }
}
void ServerMainWindow::initUI()
{
    startAction = new QAction(QIcon(":/pic/start.png"),tr("start"),this);
    stopAction = new QAction(QIcon(":/pic/stop.png"),tr("stop"),this);
    quit = new QAction(tr("quit"),this);
    killThread = new QAction(QIcon(":/pic/kill.png"),tr("kill"),this);
    showLog = new QAction(tr("show"),this);
    settleLog = new QAction(tr("settle"),this);
    helpAction = new QAction(tr("help"),this);

    fileMenu = new QMenu(tr("file"),this);
    logMenu = new QMenu(tr("log"),this);
    helpMenu = new QMenu(tr("help"),this);

    fileMenu->addAction(startAction);
    fileMenu->addAction(stopAction);
    fileMenu ->addAction(quit);

    logMenu->addAction(showLog);
    logMenu->addAction(settleLog);

    helpMenu->addAction(helpAction);

    ui->menubar->addMenu(fileMenu);
    ui->menubar->addMenu(logMenu);
    ui->menubar->addMenu(helpMenu);

    toolBar = new QToolBar(this);

    toolBar->addAction(startAction);
    toolBar->addAction(stopAction);
    toolBar->addSeparator();
    toolBar->addAction(killThread);

    addToolBar(toolBar);

    clientThreadTable = new TableWidget(QStringList()<<tr("id")<<tr("ip")<<tr("dev")<<tr("start time")<<tr("other"), this);
    clientThreadTable->setColumnWidth(1,90);


    devTable = new TableWidget(QStringList()<<tr("decname")<<tr("num")<<tr("state"),this);
    devNameTable = new TableWidgetDEV(QStringList()<<tr("name")<<tr("other"),this);

    clientThreadTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    devTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    devNameTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    layout0 = new QHBoxLayout;
    layout0->addWidget(devNameTable);
    ui->groupBox_3->setLayout(layout0);

    layout1 = new QHBoxLayout;
    layout1->addWidget(clientThreadTable);
    ui->groupBox->setLayout(layout1);

    layout2 = new QHBoxLayout;
    layout2->addWidget(devTable);
    ui->groupBox_2->setLayout(layout2);

    layout3 = new QVBoxLayout;
    layout3->addWidget(ui->groupBox);
    layout3->addWidget(ui->groupBox_2);


    layout4 = new QGridLayout;

    layout4->addWidget(ui->groupBox_3,0,0,1,2);
    layout4->addLayout(layout3,0,2,1,8);

    ui->centralwidget->setLayout(layout4);

}

void ServerMainWindow::connects()
{
    connect(showLog,SIGNAL(triggered()),this,SLOT(showLog_slots()));
    connect(startAction,SIGNAL(triggered()),this,SLOT(start_server()));
    connect(stopAction,SIGNAL(triggered()),this,SLOT(stop_server()));
    connect(quit,SIGNAL(triggered()),this,SLOT(close()));
}


void ServerMainWindow::showStateInfo(const QString &message)
{
    ui->statusbar->showMessage(message,3000);
}


void ServerMainWindow::showLog_slots()
{
    ShowLog *s = new ShowLog("log",0);
    s->showMaximized();
}


void ServerMainWindow::stop_server()
{

    server ->close();
    server ->prepare_stop();
    updataUI();
}


void ServerMainWindow::start_server()
{
    if (server == NULL)
    {
        server  = new CameraServer(this,8080);
        connect(server,SIGNAL(clientThreadInfo_signals(QStringList)),this,SLOT(getClientThreadInfo_slots(QStringList)));
        connect(server,SIGNAL(devThreadInfo_signals(QStringList)),this,SLOT(getDevThreadInfo_slots(QStringList)));
        connect(server,SIGNAL(devThreadClientNum_signals(QString,int)),this,SLOT(updataUI_devThreadNum(QString,int)));
        connect(server,SIGNAL(clientThreadClose_signals(int)),this,SLOT(updataUI_clientThread(int)));
        connect(server,SIGNAL(hasUnloadDev(QString)),this,SLOT(updateUI_devName(QString)));
        connect(server,SIGNAL(hasUnloadDev(QString)),this,SLOT(updataUI_devThread(QString)));
        connect(server,SIGNAL(_status_info(QString)),this,SLOT(showStateInfo(QString)));
        connect(server,SIGNAL(clientDevInfo_signals(int,QString)),this,SLOT(updataUI_clientThreadDevName(int,QString)));
        connect(this,SIGNAL(devInfoUpdataOK_signals(QString,QString)),server,SLOT(devInfoUpdate(QString,QString)));
        connect(this,SIGNAL(clientInfoUpdataOK_signals(int,QString)),server,SLOT(clientInfoUpdate(int,QString)));
        connect(clientThreadTable,SIGNAL(kill_signals(QString)),server,SLOT(killClientThread(QString)));
        connect(devTable,SIGNAL(kill_signals(QString)),server,SLOT(killDevThread(QString)));
        connect(devNameTable,SIGNAL(unload_signals(QString)),server,SLOT(killDevThread(QString)));
    }
    else
    {
        if (server->isListening())
        {
            QMessageBox::information(this,tr("Infomation!"),tr("The server is working!"));
            return;
        }
        else
        {
            server->listen(QHostAddress::Any,8080);
            server->ls_devName();
        }
    }
    initUI_devNameTable();
}

void ServerMainWindow::getClientThreadInfo_slots(const QStringList &list)
{
    QList<QTableWidgetItem*> l;
    foreach (const QString& temp, list) {
        l << (new QTableWidgetItem(temp));
    }
    clientThreadTable->addItems(l);
    LogMessage temp;
    temp.ip = list.at(1);
    temp.startTime = list.at(3);
    temp.dev_name = list.at(2);
    temp.other = list.at(4);
    logmap.insert(list.at(0).toInt(),temp);
    QString t = QTableWidgetItemsToQString(l);
    emit clientInfoUpdataOK_signals(list.at(0).toInt(),t);
}
void ServerMainWindow::getDevThreadInfo_slots(const QStringList &list)
{
    QList<QTableWidgetItem*> l;
    foreach (const QString& temp, list) {
        l << (new QTableWidgetItem(temp));
    }
    devTable->addItems(l);
    emit devInfoUpdataOK_signals(list.at(0),QTableWidgetItemsToQString(l));
}
void ServerMainWindow::updataUI_devThreadNum(const QString &name, int i)
{
    QList<QTableWidgetItem*> temp = devTable->findItems(name,Qt::MatchCaseSensitive);
    int r;
    foreach(const QTableWidgetItem* c ,temp)
    {
        r = devTable->row(c);
        devTable->item(r,1)->setData(Qt::DisplayRole,i);
        if (i == 0)
        {
            devTable->item(r,2)->setData(Qt::DisplayRole,tr("no working"));
        }
        else
        {
            devTable->item(r,2)->setData(Qt::DisplayRole,tr("woring"));
        }
    }

    emit devInfoUpdataOK_signals(name,QTableWidgetItemsToQString(rowItems(devTable,r)));
    devNameTable->workState_slots(name,i);

}

void ServerMainWindow::updateUI_devName(const QString &name)
{
    QList<QTableWidgetItem*> temp = devNameTable->findItems(name,Qt::MatchCaseSensitive);
    foreach(const QTableWidgetItem* c ,temp)
    {
        devNameTable->removeRow(devNameTable->row(c));
    }
}
void ServerMainWindow::updataUI_clientThread(int id)
{
    QList<QTableWidgetItem*> temp = clientThreadTable->findItems(QString::number(id,10),Qt::MatchCaseSensitive);
    foreach(const QTableWidgetItem* c ,temp)
    {
        clientThreadTable->removeRow(clientThreadTable->row(c));

    }
    recordLogInfo_slots(id);

}
void ServerMainWindow::updataUI_devThread(const QString &name)
{

    QList<QTableWidgetItem*> temp = devTable->findItems(name,Qt::MatchCaseSensitive);
    foreach(const QTableWidgetItem* c ,temp)
    {
        devTable->removeRow(devTable->row(c));

    }

}
void ServerMainWindow::updataUI_clientThreadDevName(int id, const QString &name)
{

    QList<QTableWidgetItem*> temp = clientThreadTable->findItems(QString::number(id,10),Qt::MatchCaseSensitive);
    int r;
    foreach(const QTableWidgetItem* c ,temp)
    {
        r = clientThreadTable->row(c);
        clientThreadTable->item(r,2)->setData(Qt::DisplayRole,name);
    }
    emit clientInfoUpdataOK_signals(id,QTableWidgetItemsToQString(rowItems(clientThreadTable,r)));
}
void ServerMainWindow::initUI_devNameTable()
{
    QStringList l = server->getDevNames();
    qDebug()<<l.size();
    foreach (const QString& temp, l) {
        devNameTable->addItems(new TableWidgetItem(QIcon(":/pic/redStone.png"),QIcon(":/pic/greenStone.png"),temp));
    }
}
void ServerMainWindow::recordLogInfo_slots(int id)
{
    QDir Dir("log/");
    if (!Dir.exists())
    {
        Dir.mkdir("log/");
    }
    QFile file("log/"+QDate::currentDate().toString("yyyyMMdd")+".log");
    if (!file.open(QIODevice::WriteOnly|QIODevice::Append))
    {
        return;
    }
    QTextStream out(&file);
    QMap<int,LogMessage>::iterator ite = logmap.find(id);
    if (ite != logmap.end())
    {
        out << (*ite).ip << "  "
            <<(*ite).dev_name <<"   "<<(*ite).startTime << "  "
           <<QTime::currentTime().toString("hh:mm:ss") <<"  "
          <<QTime::fromString(QString((*ite).startTime),"hh:mm:ss").msecsTo(QTime::currentTime())/1000
         <<'\n';
    }

}
void ServerMainWindow::clearTableWidget(QTableWidget *t)
{
    int counter = t->rowCount();
    while(counter)
    {
        counter = counter - 1;
        t->removeRow(counter);
    }
}
void ServerMainWindow::updataUI()
{
    clearTableWidget(devTable);
    clearTableWidget(devNameTable);
    clearTableWidget(clientThreadTable);
}
QString ServerMainWindow::QTableWidgetItemsToQString(const QList<QTableWidgetItem *> &list)
{
    QString temp;
    foreach (const QTableWidgetItem* t, list) {
        temp.append(t->text() + "  ");
    }
    return temp;
}
QList<QTableWidgetItem*> ServerMainWindow::rowItems(QTableWidget *t, int r)
{
    QList<QTableWidgetItem*> l;
    QTableWidgetItem *temp;
    for(int i = 0;i < t->columnCount();++i)
    {
        temp =  t->item(r,i);
        if (temp == NULL) continue;
        l << temp;
    }
    return l;
}
