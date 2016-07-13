#include "admincontrolwidget.h"
#include "ui_admincontrolwidget.h"

#include <QDebug>

AdminControlWidget::AdminControlWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminControlWidget)
{
    ui->setupUi(this);
    initUI();

    ui->textEdit->setContextMenuPolicy(Qt::ActionsContextMenu);
    clearContextAction = new QAction(tr("clearAll"),this);
    ui->textEdit->addAction(clearContextAction);
    initconnects();
}

AdminControlWidget::~AdminControlWidget()
{
    delete ui;
}
void AdminControlWidget::closeEvent(QCloseEvent *)
{
    hide();
    emit sig_hide();
}
void AdminControlWidget::initUI()
{

    setLayout(ui->horizontalLayout_4);
    ui->textEdit->setReadOnly(true);

}
void AdminControlWidget::initconnects()
{
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(doCMDlogDir()));
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(doCMDDevstates()));
    connect(ui->pushButton_4,SIGNAL(clicked()),this,SLOT(doCMDClientStates()));
    connect(ui->pushButton_5,SIGNAL(clicked()),this,SLOT(close()));
    connect(ui->listWidget,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(doCMDlogFile(QListWidgetItem*)));
    connect(clearContextAction,SIGNAL(triggered()),this,SLOT(slt_clear()));
}
void AdminControlWidget::doCMDlogDir()
{
    QByteArray buffer;
    cmdToByteArray(0,buffer);
    emit cmdLogDir(buffer);
}
void AdminControlWidget::doCMDlogFile(QListWidgetItem *item)
{
    QByteArray buffer;
    QDataStream out(&buffer,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_6);

    out <<(int)0;//标记数据块大小
    out << isCMD;

    out <<1;
    out << item->text();

    out.device()->seek(0);
    out << (int)(buffer.size() - sizeof(int));
    emit cmdLogFile(buffer);
}
void AdminControlWidget::doCMDDevstates()
{
    QByteArray buffer;
    cmdToByteArray(3,buffer);
    emit cmdDevStates(buffer);
}
void AdminControlWidget::doCMDClientStates()
{
    QByteArray buffer;
    cmdToByteArray(2,buffer);
    emit cmdClientStates(buffer);
}

void AdminControlWidget::getDirInfo_slots(const QByteArray &context)
{
    ui->listWidget->clear();
    QString temp(context);
    QStringList dir = temp.split('\n');
    ui->listWidget->addItems(dir);
}
void AdminControlWidget::getInfo_slots(const QByteArray &context)
{
    ui->textEdit->append(QString(context));
}
void AdminControlWidget::cmdToByteArray(int flag, QByteArray &buffer)
{
    QDataStream out(&buffer,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_6);

    out <<(int)0;
    out << isCMD;

    out <<flag;

    out.device()->seek(0);
    out << (int)(buffer.size() - sizeof(int));
}
void AdminControlWidget::slt_clear()
{
    ui->textEdit->clear();
}

