/******************************************
 *数据块长度 isCMD 命令代号       命令内容

                  0          logDir
                  1+文件名    logfile
                  2          workingDevinfo
                  3          clientinfo
                  4          devinfo
 *
 *
 *
 *
 ************************************************/




#include "clientmainwindow.h"
#include "ui_clientmainwindow.h"
#include "clientsocket.h"
#include "inputadminpassworddialog.h"
#include "admincontrolwidget.h"
//#include "recordavi.h"

#include <QMessageBox>
#include <QDebug>

ClientMainWindow::ClientMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ClientMainWindow),
    isAdmin(false),
    isRecordavi(false),
    isQuitNormal(false)
{
    ui->setupUi(this);
    initUI();
    socketInit();


    image = new QImage();


    connects();
    w = new AdminControlWidget;
    connect(w,SIGNAL(cmdClientStates(QByteArray)),this,SLOT(writeCmdContext(QByteArray)));
    connect(w,SIGNAL(cmdLogDir(QByteArray)),this,SLOT(writeCmdContext(QByteArray)));
    connect(w,SIGNAL(cmdLogFile(QByteArray)),this,SLOT(writeCmdContext(QByteArray)));
    connect(w,SIGNAL(cmdDevStates(QByteArray)),this,SLOT(writeCmdContext(QByteArray)));
    connect(w,SIGNAL(sig_hide()),this,SLOT(slt_adminControlDestroyed()));
    connect(this,SIGNAL(clientinfo_signals(QByteArray)),w,SLOT(getInfo_slots(QByteArray)));
    connect(this,SIGNAL(workingDevinfo_signals(QByteArray)),w,SLOT(getInfo_slots(QByteArray)));
    connect(this,SIGNAL(logfile_signals(QByteArray)),w,SLOT(getInfo_slots(QByteArray)));
    connect(this,SIGNAL(logdir_signals(QByteArray)),w,SLOT(getDirInfo_slots(QByteArray)));



}

ClientMainWindow::~ClientMainWindow()
{
    delete ui;
    delete image;
    delete w;
}
void ClientMainWindow::initUI()
{
    fileMenu = new QMenu(tr("file"),this);
    adminMenu = new QMenu(tr("admin"),this);
    helpMenu = new QMenu(tr("help"),this);


    action_recordAVI = new QAction(tr("recordAVI"),this);
    stopRecordAVI = new QAction(tr("stopAVI"),this);
    quit = new QAction(tr("quit"),this);
    adminLogin = new QAction(tr("adminLogin"),this);
    help = new QAction(tr("help"),this);


    fileMenu->addAction(action_recordAVI);
    fileMenu->addAction(stopRecordAVI);
    fileMenu->addAction(quit);
    adminMenu->addAction(adminLogin);
    helpMenu->addAction(help);

    ui->menubar->addMenu(fileMenu);
    ui->menubar->addMenu(adminMenu);
    ui->menubar->addMenu(helpMenu);

    ui->pushButton_2->setDisabled(true);
    adminLogin->setDisabled(true);

    action_recordAVI->setDisabled(true);
    stopRecordAVI->setDisabled(true);
}

void ClientMainWindow::closeEvent(QCloseEvent *)
{
    quit_slots();
}
void ClientMainWindow::connects()
{
    connect(adminLogin,SIGNAL(triggered()),this,SLOT(slt_adminControl()));
    connect(quit,SIGNAL(triggered()),this,SLOT(quit_slots()));
    connect(help,SIGNAL(triggered()),this,SLOT(help_slots()));
    connect(action_recordAVI,SIGNAL(triggered()),this,SLOT(recordAVI_slots()));
    connect(stopRecordAVI,SIGNAL(triggered()),this,SLOT(slt_stopRecordAVI()));
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(slt_openDevName()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(slt_closeDev()));
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(slt_canRecordAVI()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(slt_canNotRecordAVI()));
}

void ClientMainWindow::socketInit()
{
    voideSocket = new ClientSocket(this);
    cmdSocket = new ClientSocket(this);

    connect(voideSocket,SIGNAL(videoDataCome(QByteArray)),this,SLOT(videoData_slots(QByteArray)));

    connect(voideSocket,SIGNAL(returnCmdContext(int,QByteArray)),this,SLOT(cmdData_slots(int,QByteArray)));
    connect(cmdSocket,SIGNAL(returnCmdContext(int,QByteArray)),this,SLOT(cmdData_slots(int,QByteArray)));
    connect(cmdSocket,SIGNAL(sig_isAdmin(int)),this,SLOT(isAdmin_slots(int)));
    connect(voideSocket,SIGNAL(disconnected()),this,SLOT(slt_networkException()));
    connect(cmdSocket,SIGNAL(disconnected()),this,SLOT(slt_networkException()));
}

void ClientMainWindow::recordAVI_slots()
{
    recordavi = new RecordAVI();
    recordaviThread = new QThread();
    recordavi->moveToThread(recordaviThread);
    connect(this,SIGNAL(sig_recordavi(QImage)),recordavi,SLOT(getImage(QImage)));
    recordaviThread->start();
    isRecordavi = true;
    action_recordAVI->setDisabled(true);
    stopRecordAVI->setDisabled(false);

}
void ClientMainWindow::slt_stopRecordAVI()
{
    isRecordavi = false;
    recordaviThread->quit();
    recordaviThread->wait();
    recordavi->deleteLater();
    action_recordAVI->setDisabled(false);
    stopRecordAVI->setDisabled(true);

}
void ClientMainWindow::quit_slots()
{
    isQuitNormal = true;
    QApplication::quit();
}

void ClientMainWindow::help_slots()
{
    QApplication::aboutQt();
}
void ClientMainWindow::videoData_slots(const QByteArray &data)
{
    image->loadFromData(data);
    ui->label_2->setPixmap(QPixmap::fromImage(*image,Qt::AutoColor));
    if (isRecordavi) {
        emit sig_recordavi(*image);
    }

}
void ClientMainWindow::cmdData_slots(int cmd, const QByteArray &data)
{
    switch (cmd) {
    case 0:{
        emit logdir_signals(data);

    } break;
    case 1:{
        emit logfile_signals(data);

    } break;
    case 3:{
        emit workingDevinfo_signals(data);

    } break;
    case 2:{
        emit clientinfo_signals(data);

    } break;
    case 4:{
        devinfo(data);
    } break;
    default:
        break;
    }
}
void ClientMainWindow::devinfo(const QByteArray &context)
{
    QString temp(context);
    QStringList devs = temp.split('\n');
    devs.removeOne("");
    ui->comboBox->addItems(devs);
}
void ClientMainWindow::writeCmdContext(const QByteArray &context)
{
    cmdSocket->writeCMD(context);
}

void ClientMainWindow::setIPandPort(const QString &add, int p)
{
    address = add;
    port = p;
}
void ClientMainWindow::isAdmin_slots(int flag)
{
    if (0 == flag) {
        isAdmin = true;
        adminLogin->setDisabled(false);
        requestDEVname();
        emit adminLoginResult_signals();
        showMaximized();

    }
    else {
        if (2 == flag) {
            emit sig_loginError();
        }
        else {
            requestDEVname();
            cmdSocket->close();
            emit adminLoginResult_signals();
            showMaximized();
        }
    }

}
void ClientMainWindow::writeAdminNamePassWord(const QString &name, const QString &password)
{
    if (!cmdSocketConnectHost()) {

        emit connectError();
    }
    QByteArray buffer;
    QDataStream out(&buffer,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_6);

    out <<(int)0;
    out << isADMIN;
    out << name;

    out <<password;

    out.device()->seek(0);
    out << (int)(buffer.size() - sizeof(int));

    cmdSocket->writeCMD(buffer);
}
void ClientMainWindow::adminOK()
{

}
bool ClientMainWindow::cmdSocketConnectHost()
{
    if (cmdSocket->state() == QAbstractSocket::ConnectedState)
    {

        return true;
    }
    cmdSocket->connectToHost(address,port);
    if(!cmdSocket ->waitForConnected(3000))
    {

        return false;
    }
    return true;
}
void ClientMainWindow::requestDEVname()
{
    voideSocketConnectHost();
    QByteArray buffer;
    QDataStream out(&buffer,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_6);

    out <<(int)0;
    out << isCMD;
    out << 4;
    out.device()->seek(0);
    out << (int)(buffer.size() - sizeof(int));

    voideSocket->writeCMD(buffer);

}
void ClientMainWindow::slt_openDevName()
{
    if (!voideSocketConnectHost()) {
        QMessageBox::information(this,QObject::trUtf8("提示"),QObject::trUtf8("无法连接到主机!"));
    }

    QString devName = ui->comboBox->currentText();
    QByteArray buffer;
    QDataStream out(&buffer,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_6);

    out <<(int)0;
    out << isCam;
    out << devName;
    out.device()->seek(0);
    out << (int)(buffer.size() - sizeof(int));

    voideSocket->writeCMD(buffer);

    ui->pushButton->setDisabled(true);
    ui->pushButton_2->setDisabled(false);
}
bool ClientMainWindow::voideSocketConnectHost()
{
    if (voideSocket->state() == QAbstractSocket::ConnectedState)
    {
        return true;
    }
    voideSocket->connectToHost(address,port);
    if(!voideSocket ->waitForConnected(3000))
    {

        return false;
    }
    return true;

}
void ClientMainWindow::slt_closeDev()
{
    isQuitNormal = true;
    voideSocket->close();
    ui->pushButton->setDisabled(false);
    ui->pushButton_2->setDisabled(true);
}
void ClientMainWindow::slt_adminControl()
{
    //cmdSocketConnectHost();
    /*AdminControlWidget **//*w = new AdminControlWidget;
    connect(w,SIGNAL(cmdClientStates(QByteArray)),this,SLOT(writeCmdContext(QByteArray)));
    connect(w,SIGNAL(cmdLogDir(QByteArray)),this,SLOT(writeCmdContext(QByteArray)));
    connect(w,SIGNAL(cmdLogFile(QByteArray)),this,SLOT(writeCmdContext(QByteArray)));
    connect(w,SIGNAL(cmdDevStates(QByteArray)),this,SLOT(writeCmdContext(QByteArray)));
    connect(w,SIGNAL(destroyed()),this,SLOT(slt_adminControlDestroyed()));
    connect(this,SIGNAL(clientinfo_signals(QByteArray)),w,SLOT(getInfo_slots(QByteArray)));
    connect(this,SIGNAL(workingDevinfo_signals(QByteArray)),w,SLOT(getInfo_slots(QByteArray)));
    connect(this,SIGNAL(logfile_signals(QByteArray)),w,SLOT(getInfo_slots(QByteArray)));
    connect(this,SIGNAL(logdir_signals(QByteArray)),w,SLOT(getDirInfo_slots(QByteArray)));*/
    if (w->isHidden()) {
        w->showMaximized();
    }
}
void ClientMainWindow::slt_canRecordAVI()
{
    action_recordAVI->setDisabled(false);
    stopRecordAVI->setDisabled(true);
}
void ClientMainWindow::slt_canNotRecordAVI()
{
    if (isRecordavi) {
        slt_stopRecordAVI();
    }
    action_recordAVI->setDisabled(true);
    stopRecordAVI->setDisabled(true);
}
void ClientMainWindow::slt_networkException()
{
    if (!isQuitNormal) {
        QMessageBox::warning(this,tr("Waring"),tr("network Exception!"));
        QApplication::quit();
    }
    isQuitNormal = false;

}
void ClientMainWindow::slt_adminControlDestroyed()
{
    isQuitNormal = true;
    //cmdSocket->disconnectFromHost();
}
