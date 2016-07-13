#include "inputhostaddressdialog.h"
#include "ui_inputhostaddressdialog.h"

#include <QHostAddress>
#include <QMessageBox>
#include <QFile>

InputhostAddressDialog::InputhostAddressDialog(QWidget *parent, const QString &filename) :
    QDialog(parent),
    ui(new Ui::InputhostAddressDialog),
    networkConfigureFile(filename)
{
    ui->setupUi(this);
    setLayout(ui->verticalLayout_2);
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(okButton_slots()));
    hostoryDataRead();
    connect(ui->comboBox,SIGNAL(activated(QString)),this,SLOT(slt_selectHostoryData(QString)));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(slt_clearHostoryData()));
    setDefaultIPandPort();
    setModal(true);
}

InputhostAddressDialog::~InputhostAddressDialog()
{
    delete ui;
}

void InputhostAddressDialog::okButton_slots()
{
    QString address = ui->comboBox->currentText();
    QHostAddress add;
    if (!add.setAddress(address))
    {
        QMessageBox::information(this,tr("information"),tr("IP is invail! "));
        return;
    }

    bool isInt;
    QString port = ui->lineEdit->text();
    int p = port.toInt(&isInt,10);
    if (!isInt)
    {
        QMessageBox::information(this,tr("information"),tr("Port is invail! "));
        return;
    }

    emit hostAdress_signals(address,p);
    hostoryDataWrite();
    close();
}
void InputhostAddressDialog::hostoryDataRead()
{
    QFile file(networkConfigureFile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::information(this,tr("Infomation!"),tr("Read hostory data fail!"));
        return;
    }

    QTextStream out(&file);
    QString temp = out.readLine();
    while (!temp.isNull()) {
        ui->comboBox->addItem(temp.left(temp.indexOf(' ')));
        temp = out.readLine();
    }
    file.close();

}
void InputhostAddressDialog::slt_selectHostoryData(const QString indextext)
{
    QFile file(networkConfigureFile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::information(this,tr("Infomation!"),tr("Read hostory data fail!"));
        return;
    }

    QTextStream out(&file);
    QString temp = out.readLine();
    while (!temp.isNull()) {
        if (temp.left(temp.indexOf(' ')) == indextext) {
            ui->lineEdit->setText(temp.right(temp.length() - temp.indexOf(' ') - 1));
            file.close();
            return;
        }
        temp = out.readLine();
    }
    file.close();

}
void InputhostAddressDialog::slt_clearHostoryData()
{
    QFile file(networkConfigureFile);

    file.resize(0);
    ui->comboBox->clear();
}
void InputhostAddressDialog::hostoryDataWrite()
{
    QFile file(networkConfigureFile);
    if (!file.open(QIODevice::ReadWrite /*| QIODevice::Append*/ | QIODevice::Text)) {
        QMessageBox::information(this,tr("Infomation!"),tr("Read hostory data fail!"));
        return;
    }

    QTextStream out(&file);
    QString temp = out.readLine();
    while (!temp.isNull()) {

        if (ui->comboBox->currentText() == temp.left(temp.indexOf(' '))) {
            file.close();
            return;
        }
        temp = out.readLine();
    }
    out << ui->comboBox->currentText() << ' ' << ui->lineEdit->text() << '\n';
    file.close();

}
void InputhostAddressDialog::setDefaultIPandPort()
{
    QFile file(networkConfigureFile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::information(this,tr("Infomation!"),tr("Read hostory data fail!"));
        return;
    }

    QTextStream out(&file);
    QString temp = out.readLine();
    defaultIP = temp.left(temp.indexOf(' '));
    defaultPort = temp.right(temp.length() - temp.indexOf(' ') - 1).toInt();
    file.close();
}
