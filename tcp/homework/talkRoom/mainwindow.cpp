/********************************************************************
* author 周翔
* e-mail 604487178@qq.com
* blog http://blog.csdn.net/zhx6044
**********************************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    quitNormal(false)
{
    ui->setupUi(this);

    ui->pushButton->setDefault(true);

    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(slt_sendMessage()));
    connect(&c_socket,SIGNAL(readyRead()),this,SLOT(slt_reciveMessage()));
    connect(&c_socket,SIGNAL(disconnected()),this,SLOT(slt_NetworkError()));
    connect(ui->action,SIGNAL(triggered()),this,SLOT(slt_connect()));
    connect(ui->action_3,SIGNAL(triggered()),this,SLOT(slt_about()));
    connect(ui->action_2,SIGNAL(triggered()),this,SLOT(close()));




    setWindowTitle("TalkRoom");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::closeEvent(QCloseEvent *e)
{
    quitNormal = true;
    if(c_socket.isOpen()) {
        c_socket.disconnectFromHost();
    }
    QMainWindow::closeEvent(e);
}

void MainWindow::slt_setIPandPort(const QString &v_ip, int v_port)
{
    QHostAddress address;
    ip = v_ip;
    port = v_port;
    address.setAddress(ip);
    emit sig_makeSomeOneClose();
    c_socket.connectToHost(address,port);
    if (c_socket.waitForConnected(3000)) {
        ui->textEdit->append("connect successfily!");
    } else {
        ui->textEdit->append("connect fauily!" + c_socket.error());
    }
}

void MainWindow::slt_sendMessage()
{
    QString message = ui->textEdit_2->toPlainText();
    ui->textEdit_2->clear();
    if (c_socket.state() == QTcpSocket::ConnectedState) {
        c_socket.write(message.toLatin1());
        ui->textEdit->append(QTime::currentTime().toString("hh:mm:ss") +"    "+ message);
    } else {

    }
}
void MainWindow::slt_reciveMessage()
{
   // QByteArray message = c_socket.readAll();
    ui->textEdit->append(c_socket.readAll());
}

void MainWindow::slt_NetworkError()
{
    if (!quitNormal)
        QMessageBox::warning(this, tr("ERROR"), tr("NetWork ERROR!"));
}

void MainWindow::slt_connect()
{
    SettingDialog dialog(this);
    dialog.setModal(true);
    connect(&dialog,SIGNAL(sig_IpAndPort(QString,int)),this,SLOT(slt_setIPandPort(QString,int)));
    connect(this,SIGNAL(sig_makeSomeOneClose()),&dialog,SLOT(close()));
    dialog.show();
    dialog.exec();
}

void MainWindow::slt_about()
{
    QApplication::aboutQt();
}
