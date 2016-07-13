#include "showlog.h"
#include "ui_showlog.h"
#include <QDir>
#include <QDebug>
#include <QMessageBox>


ShowLog::ShowLog(const QString &dir, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowLog),
    dirName(dir)
{
    ui->setupUi(this);

    openFile = new QAction(tr("openFile"),0);
    removeFile = new QAction(tr("removeFile"),0);

    ui->treeWidget->addAction(openFile);
    ui->treeWidget->addAction(removeFile);

    setcolor();

    connect(ui->treeWidget,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(openFile_slots()));


    connect(openFile,SIGNAL(triggered()),this,SLOT(openFile_slots()));
    connect(removeFile,SIGNAL(triggered()),this,SLOT(removeFile_slots()));


    ui->treeWidget->setContextMenuPolicy(Qt::ActionsContextMenu);

    mainLayout = new QGridLayout;
    mainLayout->addWidget(ui->treeWidget,0,0,1,2);
    mainLayout->addWidget(ui->textEdit,0,2,1,8);
    setLayout(mainLayout);

    QTreeWidgetItem *top = new QTreeWidgetItem(ui->treeWidget,QStringList()<<dirName);

    QDir Dir(dirName);
    if (!Dir.exists())
    {
        Dir.mkdir(dirName);
    }
    QFileInfoList infolist = Dir.entryInfoList(QStringList()<<tr("*.log"),QDir::Files|QDir::Dirs,QDir::Name);

    foreach(const QFileInfo &temp,infolist)
    {
        ui->treeWidget->addTopLevelItem(new QTreeWidgetItem(top,QStringList() << temp.fileName()));
    }
}

ShowLog::~ShowLog()
{
    delete ui;
}
void ShowLog::openFile_slots()
{
    QTreeWidgetItem *temp = ui->treeWidget->currentItem();
    if (temp == NULL || temp == ui->treeWidget->topLevelItem(0))
    {
        return;
    }
    ui->textEdit->clear();
    QString fileName = temp->data(0,Qt::EditRole).toString();
    QFile file(dirName+"/" + fileName);
    if (!file.open(QFile::ReadOnly))
    {
        QMessageBox::information(this,tr("Infomation!"),tr("open %1 error!").arg(fileName));
        return;
    }
    openFileName = fileName;
    QTextStream in(&file);
    ui->textEdit->append(in.readAll());
    file.close();




}
void ShowLog::removeFile_slots()
{
    QTreeWidgetItem *temp = ui->treeWidget->currentItem();
    if (temp == NULL)
    {
        return;
    }
    QString fileName = temp->data(0,Qt::EditRole).toString();

    QFile file(dirName+"/" + fileName);
    if (file.remove())
    {
        if (openFileName == fileName)
            ui->textEdit->clear();
        openFileName = "";
        delete temp;
    }
    else
    {
        QMessageBox::information(this,tr("Infomation!"),tr("remove %1 error1").arg(fileName));
        return;
    }

}
void ShowLog::setcolor()
{
    QPalette pa = ui->textEdit->palette();
    pa.setColor(QPalette::Base,QColor(0x30,0x0A,0x24));
    ui->textEdit->setPalette(pa);
    pa.setColor(QPalette::Text,QColor(Qt::white));
    ui->textEdit->setPalette(pa);
    pa.setColor(QPalette::Highlight,QColor(Qt::white));
    ui->textEdit->setPalette(pa);
    pa.setColor(QPalette::HighlightedText,QColor(Qt::black));
    ui->textEdit->setPalette(pa);
}
