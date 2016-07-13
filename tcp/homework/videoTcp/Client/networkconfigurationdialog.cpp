#include "networkconfigurationdialog.h"
#include "ui_networkconfigurationdialog.h"

NetworkConfigurationDialog::NetworkConfigurationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NetworkConfigurationDialog)
{
    ui->setupUi(this);
}

NetworkConfigurationDialog::~NetworkConfigurationDialog()
{
    delete ui;
}
