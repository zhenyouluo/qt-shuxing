#include "inputadminpassworddialog.h"
#include "ui_inputadminpassworddialog.h"
#include "inputhostaddressdialog.h"

#include <QMessageBox>
#include <QFile>
#include <QTextStream>

InputAdminPasswordDialog::InputAdminPasswordDialog(QWidget *parent, const QString &filename) :
    QDialog(parent),
    ui(new Ui::InputAdminPasswordDialog)
{
    ui->setupUi(this);
    setLayout(ui->verticalLayout);
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(okButton_slots()));
    connect(ui->pushButton,SIGNAL(clicked()),this,SIGNAL(sig_quit()));
    networkConfigureDialog = new InputhostAddressDialog(this,filename);
    connect(networkConfigureDialog,SIGNAL(hostAdress_signals(QString,int)),this,SLOT(slt_IpAndPortConfigure(QString,int)));
    connect(ui->pushButton_3,SIGNAL(clicked()),networkConfigureDialog,SLOT(show()));
    ui->pushButton_2->setDefault(true);
    connect(ui->comboBox,SIGNAL(activated(QString)),this,SLOT(slt_comboxIsSelected(QString)));
    connect(ui->pushButton_4,SIGNAL(clicked()),this,SLOT(slt_clearHistoryData()));
    readLoginInfo();

}

InputAdminPasswordDialog::~InputAdminPasswordDialog()
{
    delete ui;
}
void InputAdminPasswordDialog::showEvent(QShowEvent *)
{
    emit sig_IpAndPort(networkConfigureDialog->getIP(),networkConfigureDialog->getPort());
}
void InputAdminPasswordDialog::okButton_slots()
{
    QString name = ui->comboBox->currentText();
    QString password = ui->lineEdit_2->text();
    if (name.isEmpty() || password.isEmpty())
    {
        QMessageBox::information(this,tr("information"),tr("is Empty!"));
        return;
    }

    emit adminInfo_signals(name,password);
    if (ui->checkBox->checkState() != Qt::Unchecked)
        writeNamePasswordIntoFile(name,password);
}
void InputAdminPasswordDialog::slt_IpAndPortConfigure(const QString &ip, int port)
{
    emit sig_IpAndPort(ip,port);
}
void InputAdminPasswordDialog::slt_connectError()
{
    QMessageBox::information(this,QObject::trUtf8("提示"),QObject::trUtf8("无法连接到主机，请查看网络配置!"));
}
void InputAdminPasswordDialog::slt_loginError()
{
    QMessageBox::information(this,QObject::trUtf8("提示"),QObject::trUtf8("登录失败!"));
}
void InputAdminPasswordDialog::writeNamePasswordIntoFile(const QString &name, const QString &password)
{
    QFile file("historyLogin.txt");
    if (!file.open(QIODevice::WriteOnly|QIODevice::Text)) {
        return;
    }
    QTextStream in(&file);
    in << name << ' ' << password << '\n';

    file.close();
}
void InputAdminPasswordDialog::readLoginInfo()
{
    QFile file("historyLogin.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::information(this,tr("Infomation!"),tr("Read hostory data fail!"));
        return;
    }

    QTextStream out(&file);
    QString temp = out.readLine();
    while (!temp.isNull()) {
        NamePasswordQPair t;
        t.first = temp.left(temp.indexOf(' '));
        t.second = temp.right(temp.length() - temp.indexOf(' ') - 1);
        list_namepassword.append(t);
        temp = out.readLine();
        ui->comboBox->addItem(t.first);
    }
    file.close();

}
void InputAdminPasswordDialog::slt_comboxIsSelected(const QString &text)
{
    foreach (const NamePasswordQPair& t, list_namepassword) {
        if (text == t.first) {
            ui->lineEdit_2->setText(t.second);
            return;
        }

    }
}

void InputAdminPasswordDialog::slt_clearHistoryData()
{
    QFile file("historyLogin.txt");
    file.resize(0);
    list_namepassword.clear();
    ui->comboBox->clear();
    ui->lineEdit_2->clear();
}
