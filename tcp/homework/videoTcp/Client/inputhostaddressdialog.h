/*****************
 *
 *网络配置窗口
 *暂时不支持同一ip不同端口的历史数据保存
 *
 *************************/

#ifndef INPUTHOSTADDRESSDIALOG_H
#define INPUTHOSTADDRESSDIALOG_H

#include <QDialog>

namespace Ui {
class InputhostAddressDialog;
}

class InputhostAddressDialog : public QDialog
{
    Q_OBJECT
signals:
    void hostAdress_signals(const QString& address,int port);
public:
    explicit InputhostAddressDialog(QWidget *parent = 0,const QString &filename = "networkConfigureFile.conf");
    ~InputhostAddressDialog();
    QString getIP() const {return defaultIP;}
    int getPort() const {return defaultPort;}
protected:
private slots:
    void okButton_slots();
    void slt_selectHostoryData(const QString indextext);
    void slt_clearHostoryData();
private:
    Ui::InputhostAddressDialog *ui;
    QString networkConfigureFile;//网络配置文件
    QString defaultIP;
    int defaultPort;

    void hostoryDataRead();
    void hostoryDataWrite();
    void setDefaultIPandPort();

};

#endif // INPUTHOSTADDRESSDIALOG_H
