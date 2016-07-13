#include "ServerSocket.h"

#include <QFile>
#include <QStringList>

ServerSocket::ServerSocket(QObject *parent, int handle, PERMISSION p):
    QTcpSocket(parent),
    socket_id(handle),
    per(p),
    blockSize(0)
{
    this ->setSocketDescriptor(handle);
    connect(this,SIGNAL(readyRead()),this,SLOT(dataReceived()));
    connect(this,SIGNAL(disconnected()),this,SLOT(slotDisconnected()));
}
void ServerSocket::dataReceived()//读出客户端操作的设备的名和操作指令,现在在此的动作为伪动作
{
    QDataStream in(this);
    in.setVersion(QDataStream::Qt_4_6);
    if (blockSize == 0)
    {
        if (this->bytesAvailable() < sizeof(int))
        {
            return;
        }
        in >> blockSize;
    }
    if (this->bytesAvailable() < blockSize)
    {
        return;
    }
    blockSize = 0;
    int type = 0;
    in >> type;
    switch (type) {
    case isCam:
    {
        QString devName;
        in >> devName;
        emit open_dev(devName,socket_id);
    }break;
    case isADMIN:
    {
        QString user;
        QString password;
        in >>user;
        in >> password;
        int result = isAdmin(user,password);
        if (result == 0)
        {
            per = ADMIN;
            loginResult(0);
        }
        else
        {
            if (result == 1) {
                loginResult(1);
            }
            else {
                loginResult(2);
            }

        }
    }break;
    case isCMD:
    {
        int cmd = 0;
        in >> cmd;
        QString argv;
        in >> argv;
        if(per == ADMIN)
        {
            emit dealWithCMD_signals(cmd,argv,socket_id);
        }
        else {
            if (cmd == 4) {
                emit dealWithCMD_signals(cmd,argv,socket_id);
            }
        }
    }break;
    default:
        break;
    }
}
void ServerSocket::slotDisconnected()//连接断开
{
    emit disconnected(this ->socket_id);
}
int ServerSocket::isAdmin(const QString &user, const QString &password)
{
    QFile file("password.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return -1;
    QTextStream out(&file);
    QString temp = out.readLine();
    while (!temp.isNull()) {
        QStringList list(temp.split(' '));
        if (list.at(0) == user && list.at(1) == password &&list.at(2) == "0") {
            return 0;
        }
        if (list.at(0) == user && list.at(1) == password &&list.at(2) == "1") {
            return 1;
        }
        temp = out.readLine();

    }
    return 2;
}
void ServerSocket::loginResult(int flag)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_6);

    out << (int)0;
    out << isADMIN;

    out << flag;

    out.device()->seek(0);
    out << (int)(block.size() - sizeof(int));

    this->write(block);
}
