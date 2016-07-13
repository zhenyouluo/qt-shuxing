#ifndef INPUTADMINPASSWORDDIALOG_H
#define INPUTADMINPASSWORDDIALOG_H

#include <QDialog>

typedef QPair<QString,QString> NamePasswordQPair;

class InputhostAddressDialog;

namespace Ui {
class InputAdminPasswordDialog;
}

class InputAdminPasswordDialog : public QDialog
{
    Q_OBJECT
signals:
    void adminInfo_signals(const QString& name,const QString &password);
    void sig_IpAndPort(const QString &ip,int port);
    void sig_quit();
public:
    explicit InputAdminPasswordDialog(QWidget *parent = 0,const QString &filename = "networkConfigureFile.conf");
    ~InputAdminPasswordDialog();

public slots:
    void slt_connectError();
    void slt_loginError();
protected:
    void showEvent(QShowEvent *);

private slots:
    void okButton_slots();
    void slt_IpAndPortConfigure(const QString &ip,int port);//接受自定义的网络配置
    void slt_comboxIsSelected(const QString &text);
    void slt_clearHistoryData();
private:  
    Ui::InputAdminPasswordDialog *ui;
    InputhostAddressDialog *networkConfigureDialog;

    QList<NamePasswordQPair> list_namepassword;

    void writeNamePasswordIntoFile(const QString& name,const QString& password);
    void readLoginInfo();
};

#endif // INPUTADMINPASSWORDDIALOG_H
