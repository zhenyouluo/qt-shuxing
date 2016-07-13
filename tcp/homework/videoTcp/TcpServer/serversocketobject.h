#ifndef SERVERSOCKETOBJECT_H
#define SERVERSOCKETOBJECT_H

#include <QObject>
#include <QImage>
#include <QDebug>
#include <QHostAddress>

#include "ServerSocket.h"

class ServerSocketObject : public QObject
{
    Q_OBJECT
public:
    explicit ServerSocketObject(QObject *parent = 0,int consumer_socket = 0);
    ~ServerSocketObject(){qDebug()<<"!!ServerSocketObject";}
    int getSocketId() const{return workSocket ->socketDescriptor();}
  //  void mySignals(int i){emit free_WriteThread(i);}
    QString getClientIP() const {return workSocket->peerAddress().toString();}
    void socketClose() {workSocket->close();}

signals:
    void send_dev_name(const QString&,int);
    void free_WriteThread(int);
    void serverDealWithCMD_signals(int cmd,const QString&argv,int handle);//向server请求服务，对ServerSocket中dealWithCMD_signals的封装
public slots:
    void writeContext(const QByteArray&context) {workSocket->write(context);}
    //void get_error(const QString&);
    void devWillClose_slots() {workSocket->disconnectFromHost();}

private:
    ServerSocket *workSocket;
    int _size;
;

};

#endif // SERVERSOCKETOBJECT_H
