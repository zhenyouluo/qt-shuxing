/********************************************************************
* author 周翔
* e-mail 604487178@qq.com
* blog http://blog.csdn.net/zhx6044
**********************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QHostAddress>
#include <QMessageBox>
#include <QTime>

#include "settingdialog.h"



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void slt_setIPandPort(const QString &v_ip, int v_port);
signals:
    void sig_makeSomeOneClose();
protected:
    void closeEvent(QCloseEvent *e);
private slots:
    void slt_sendMessage();
    void slt_reciveMessage();
    void slt_NetworkError();
    void slt_connect();
    void slt_about();
private:
    Ui::MainWindow *ui;

    QString ip;
    int port;
    QTcpSocket c_socket;

    bool quitNormal;
};

#endif // MAINWINDOW_H
