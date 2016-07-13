#ifndef ServerSocket_H
#define ServerSocket_H

#include <QTcpSocket>
#include "Permission.h"

#include "CommandType.h"

class ServerSocket : public QTcpSocket
{
    Q_OBJECT
public:
    ServerSocket(QObject *parent = 0,int handle = 0,PERMISSION p = NORMAL);
    virtual ~ServerSocket() {}
signals:
    void open_dev(const QString&,int);//客服端要求打开的设备名称
    void disconnected(int);//断开时发送给server，通知那个连接断开
    void dealWithCMD_signals(int cmd,const QString&argv,int handle);
protected slots:
    void dataReceived();//读取客服端发来的信息，根据信息来就行相关的操作
    void slotDisconnected();//连接断开时调用
private:
    int socket_id;
    PERMISSION per;
    int blockSize;//数据块大小

    int isAdmin(const QString& user,const QString& password);
    void loginResult(int flag);
};

#endif // ServerSocket_H
