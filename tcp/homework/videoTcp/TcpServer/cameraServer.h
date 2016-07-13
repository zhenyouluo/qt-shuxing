/**************************************************
  *author Zhou Xiang
  *Copyright
  *function 一个TCP服务端
  *下面需要做的：1.在启动时扫描设备，和查看状态（目前只扫描设备文件，没有对设备是否可用进行查询）
  *           2.怎么样实现一个设备多个用户的功能（目前已经实现功能，但是此资源占用大，有待改进）
              3.怎么样实现和优化与客户端的信息交换，以及功能控制
              4.将服务端的设备信息发送到客服端，以供客服查阅
  *************************************************/
#ifndef CAMERASERVER_H
#define CAMERASERVER_H

#include<QtNetwork/QTcpServer>
#include<QThread>
#include<QDir>
#include<QList>
#include<QFileInfo>
#include<QFileInfoList>
#include<QMessageBox>
#include<QTime>
#include<QProcess>
#include<QApplication>


class ServerSocket;
class ServerSocketObject;
class CameraThread;


class CameraServer : public QTcpServer
{
    Q_OBJECT
public:
    CameraServer(QObject *parent = 0,int port = 0,const QString &logDir = "log/");
    virtual ~CameraServer();
    void prepare_stop();
    void ls_devName();
    QList<QString> getDevNames() const{ return dev_name_list;}
signals:
    void _status_info(const QString&);//发送服务端相关的工作的信息
    void _error(const QString&);//相关的错误信息

    //更新UI的
    void clientThreadInfo_signals(const QStringList&);
    void clientDevInfo_signals(int id,const QString& name);
    void clientThreadClose_signals(int);
    void devThreadInfo_signals(const QStringList&);
    void devThreadClientNum_signals(const QString&,int);
    void hasUnloadDev(const QString&);

    //是对clientThreadClose_signals和hasUnloadDev的封装
    void clientClose_signals(int id,const QString&info);
    void devUnload_signals(const QString& name,const QString&info);


public slots:
    void Dev_Socket(const QString&,int);//设备线程与通讯的线程的联系建立
    void freeS_Thread(int);//连接断开时，释放服务端与客户端通讯的socket对象
    void killClientThread(const QString& id);
    void killDevThread(const QString& name);//供杀死设备线程和卸载设备共同使用

    void workClientCMD_slots(int cmd,const QString&argv,int handle);//为客服端的请求命令服务

    void clientInfoUpdate(int handle,const QString&info);
    void devInfoUpdate(const QString& name,const QString&info);
protected slots:
    void unloadDev(const QString&name, int number);
    void thread_init();//初始化所有的设备线程
private slots:
    void clientClose_slots(int id);
    void devUnload_slots(const QString& name);
protected:
    void incomingConnection(int handle);//有连接申请时自动调用
private:
    QList<QString> dev_name_list;//存放设备名
    QList<CameraThread*> dev_thread_list;//线程池的实现形式
    QList<QThread*> socket_thread_list;//服务端与客户端通讯的socket对象的工作线程
    QList<ServerSocketObject*> socket_list;//存放服务端与客户端通讯的socket对象
    QList<QString> willUnloadDevname;//将要卸载的设备名
    QList<QString> willunloadDev;
    QHash<int,QString> clientsInfo;
    QHash<QString,QString> workingDevsInfo;
    QByteArray devInfo;//设备信息

    ServerSocketObject* getServerSocket(int handle);

    QByteArray cmdLogFilesContext();
    QByteArray cmdLogFileContext(const QString &fileName);
    QByteArray cmdClientsContext();
    QByteArray cmdDevsContext();
    QByteArray cmdDevnamesContext();

    QString dir;//日志文件的目录


};

#endif // CAMERASERVER_H
