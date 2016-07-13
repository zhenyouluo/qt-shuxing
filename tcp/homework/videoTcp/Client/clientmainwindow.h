#ifndef CLIENTMAINWINDOW_H
#define CLIENTMAINWINDOW_H

#include <QMainWindow>
#include <QHostAddress>
#include <QThread>

#include <recordavi.h>



class ClientSocket;
class InputAdminPasswordDialog;
class RecordAVI;
class AdminControlWidget;

namespace Ui {
class ClientMainWindow;
}

class ClientMainWindow : public QMainWindow
{
    Q_OBJECT
signals:
    void logdir_signals(const QByteArray& context);
    void logfile_signals(const QByteArray& context);
    void workingDevinfo_signals(const QByteArray& context);
    void clientinfo_signals(const QByteArray& context);
    void devinfo_signals(const QByteArray& context);
    void adminLoginResult_signals();
    void connectError();
    void sig_loginError();
    void sig_recordavi(const QImage& frame);
public:
    explicit ClientMainWindow(QWidget *parent = 0);
    ~ClientMainWindow();
public slots:
    void videoData_slots(const QByteArray &data);//isCam
    void cmdData_slots(int cmd, const QByteArray &data);//isADMIN
    void writeCmdContext(const QByteArray&context);//isCmd

    void isAdmin_slots(int flag);
    void setIPandPort(const QString& add, int p);//接受网络配置的参数
protected:
    void closeEvent(QCloseEvent *);
private slots:
    void recordAVI_slots();
    void slt_stopRecordAVI();
    void quit_slots();
    void help_slots();
    void writeAdminNamePassWord(const QString&name,const QString&password);
    void requestDEVname();
    void slt_openDevName();
    void slt_closeDev();
    void slt_adminControl();
    void slt_canRecordAVI();
    void slt_canNotRecordAVI();
    void slt_networkException();
    void slt_adminControlDestroyed();
private:
    Ui::ClientMainWindow *ui;

    QHostAddress address;
    int port;

    QImage *image;

    QMenu *fileMenu;
    QMenu *adminMenu;
    QMenu *helpMenu;

    QAction *action_recordAVI;
    QAction *stopRecordAVI;
    QAction *quit;
    QAction *adminLogin;
    QAction *help;


    ClientSocket *voideSocket;//接受视频数据的socket
    ClientSocket *cmdSocket;//完成admin命令的socket
    RecordAVI *recordavi;
    QThread *recordaviThread;
    AdminControlWidget *w;


    void initUI();
    void connects();

    void socketInit();
    void devinfo(const QByteArray &context);
    void adminOK();
    bool cmdSocketConnectHost();
    bool voideSocketConnectHost();
    void canRecordAVI();


    bool isAdmin;

    bool isRecordavi;

    bool isQuitNormal;

};

#endif // CLIENTMAINWINDOW_H
