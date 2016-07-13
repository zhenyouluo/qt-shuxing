#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QTcpSocket>
#include <QStringList>

#include "CommandType.h"

class ClientSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit ClientSocket(QObject *parent = 0);
signals:
    void videoDataCome(const QByteArray&data);//isCan
    void returnCmdContext(int cmd, const QByteArray& context);//isCMD
    void sig_isAdmin(int);//isADMIN
public slots:
    void writeCMD(const QByteArray& context);
private slots:
    void dataComing();
private:
    int size;
    
};

#endif // CLIENTSOCKET_H
