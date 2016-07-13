#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tcpSocket=new QTcpSocket();
    tcpSocket->abort();
    tcpSocket->connectToHost("192.168.100.188",8000);
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(revData()));
    printf("111\n");
}
void MainWindow::revData(){

   // QString datas=tcpSocket->readAll();
 printf("sadasd\n");
    //printf("sadasd %s\n",datas);
}



MainWindow::~MainWindow()
{
    delete ui;
}
