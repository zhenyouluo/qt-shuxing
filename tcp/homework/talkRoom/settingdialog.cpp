/********************************************************************
* author 周翔
* e-mail 604487178@qq.com
* blog http://blog.csdn.net/zhx6044
**********************************************************************/

#include "settingdialog.h"
#include "ui_settingdialog.h"

SettingDialog::SettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDialog)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(slt_doButton()));
    setWindowTitle("Setting");
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

void SettingDialog::slt_doButton()
{
    QHostAddress address;
    if(!address.setAddress(ui->lineEdit->text().trimmed())) {
        QMessageBox::information(this, tr("Info"), tr("IP Error!"));
        return;
    }
    bool ok = false;
    int port = ui->lineEdit_2->text().toInt(&ok);
    if (ok) {
        emit sig_IpAndPort(ui->lineEdit->text(), port);
    }
}
