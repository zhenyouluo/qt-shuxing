#include "clientsocket.h"

ClientSocket::ClientSocket(QObject *parent) :
    QTcpSocket(parent),
    size(0)
{
    connect(this,SIGNAL(readyRead()),this,SLOT(dataComing()));
}
void ClientSocket::dataComing()
{
    QDataStream in(this);
    in.setVersion(QDataStream::Qt_4_6);
    if (size == 0)
    {
        if (bytesAvailable() < (qint64)sizeof(int))
        {
            return;
        }
        in >> size;
    }
    if (bytesAvailable() < size)
    {
        return;
    }
    int type = -1;
    in >> type;
    switch(type)
    {
    case isCam://video data  isCam
    {
        QByteArray buffer;
        // buffer.resize(size - sizeof(int));
        //  in >> buffer;
        buffer.resize(size - 3*sizeof(int));
        in>>buffer;
        emit videoDataCome(buffer);
    }break;
    case isCMD:
    {
        QByteArray buffer;
        int cmd;
        in >> cmd;
        buffer.resize(size - 3*sizeof(int));
        in >> buffer;
        emit returnCmdContext(cmd,buffer);
    }break;
    case isADMIN://isADMIN
    {
        int flag;
        in >> flag;
        emit sig_isAdmin(flag);
    }break;
    default:break;

    }
    size = 0;
}
void ClientSocket::writeCMD(const QByteArray &context)
{
    this->write(context);
}

