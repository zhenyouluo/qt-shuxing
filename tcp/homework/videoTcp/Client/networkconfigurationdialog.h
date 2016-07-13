#ifndef NETWORKCONFIGURATIONDIALOG_H
#define NETWORKCONFIGURATIONDIALOG_H

#include <QDialog>

namespace Ui {
class NetworkConfigurationDialog;
}

class NetworkConfigurationDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit NetworkConfigurationDialog(QWidget *parent = 0);
    ~NetworkConfigurationDialog();
    
private:
    Ui::NetworkConfigurationDialog *ui;
};

#endif // NETWORKCONFIGURATIONDIALOG_H
