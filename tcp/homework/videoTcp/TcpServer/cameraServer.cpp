#include "cameraServer.h"
#include "cameraThread.h"
#include "serversocketobject.h"
#include "ServerSocket.h"

#include <QTimer>
#include <QDebug>
CameraServer::CameraServer(QObject *parent, int port, const QString &logDir):
    QTcpServer(parent),
    devInfo(""),
    dir(logDir)
{
    this ->listen(QHostAddress::Any,port);
    ls_devName();
    connect(this,SIGNAL(clientThreadClose_signals(int)),this,SLOT(clientClose_slots(int)));
    connect(this,SIGNAL(hasUnloadDev(QString)),this,SLOT(devUnload_slots(QString)));
    connect(this,SIGNAL(clientClose_signals(int,QString)),this,SLOT(clientInfoUpdate(int,QString)));
    connect(this,SIGNAL(devUnload_signals(QString,QString)),this,SLOT(devInfoUpdate(QString,QString)));
}
CameraServer::~CameraServer()
{
    int j = dev_thread_list.size();
    for(int i = 0;i < j;++i)
    {
        dev_thread_list.at(i)->quit();
        dev_thread_list.at(i)->wait();
    }

}
void CameraServer::incomingConnection(int handle)//建立连接
{
    ServerSocketObject *_s_thread = new ServerSocketObject(0,handle);
    QString peerAddress = _s_thread->getClientIP();
    _s_thread ->setObjectName(QString::number(handle,10));
    socket_list.append(_s_thread);

    connect(_s_thread,SIGNAL(send_dev_name(QString,int)),this,SLOT(Dev_Socket(QString,int)));
    connect(_s_thread,SIGNAL(free_WriteThread(int)),this,SLOT(freeS_Thread(int)));
    connect(_s_thread,SIGNAL(serverDealWithCMD_signals(int,QString,int)),this,SLOT(workClientCMD_slots(int,QString,int)));

    emit _status_info(QTime::currentTime().toString()+QObject::trUtf8("______连接建立______")+QString::number(handle,10));



    //  QStringList list;

    emit clientThreadInfo_signals(QStringList()<<QString::number(handle,10)<<peerAddress<<QString("******")
                                  <<QDateTime::currentDateTime().toLocalTime().toString("hh:mm:ss")
                                  <<QObject::trUtf8("********"));

    //  clientInfoUpdate(handle,QStringListToQString(list));

    qDebug()<<"Socket Descriptor is"<<handle;
}
void CameraServer::ls_devName()
{
    dev_name_list.clear();
    devInfo.clear();
    QDir dir("/dev/");
    if (dir.exists())
    {
        QStringList infolist = dir.entryList(QDir::System,QDir::Name);

        foreach(const QString &temp,infolist)
        {
            //  qDebug()<<temp;
            if (temp.contains("video"))
            {
                devInfo.append("/dev/"+temp);
                devInfo.append('\n');
                dev_name_list.append("/dev/"+temp);
            }
        }
    }
    QTimer::singleShot(500,this,SLOT(thread_init()));
}

void CameraServer::thread_init()
{
    for(int i = 0;i < dev_name_list.size();++i)
    {
        QString str_file(dev_name_list.at(i));
        CameraThread *thread = new CameraThread(this,str_file);
        connect(this,SIGNAL(destroyed()),thread,SLOT(_stop()));
        thread->wait();
        dev_thread_list.append(thread);

        connect(thread,SIGNAL(clientNumber_Signals(QString,int)),this,SIGNAL(devThreadClientNum_signals(QString,int)));

        connect(thread,SIGNAL(clientNumber_Signals(QString,int)),this,SLOT(unloadDev(QString,int)));


        //  QStringList list;

        emit devThreadInfo_signals(QStringList()<<str_file<<QString::number(thread->get_client_number(),10)
                                   <<QObject::trUtf8("no working"));
        //  devInfoUpdate(str_file,list);
    }
}
void CameraServer::Dev_Socket(const QString &dev, int _s_handle)//请求视频时完成相关的线程连接
{
    ServerSocketObject *o_thread = NULL;
    CameraThread *d_thread = NULL;
    QString peerAddress;
    if(!dev_name_list.contains(dev))
    {
        emit _error("dev is not find!");//还有很多后备处理
        return;
    }

    else
    {
        for(int i = 0;i < dev_thread_list.size();++i)
        {
            if(dev_thread_list.at(i)->objectName() == dev)
            {
                d_thread = dev_thread_list.at(i);
                break;
            }
        }
        for(int j = 0;j < socket_list.size();++j)
        {
            if(socket_list.at(j)->objectName() == QString::number(_s_handle,10))
            {
                o_thread = socket_list.at(j);
                peerAddress = o_thread->getClientIP();
                break;
            }
        }

        QThread *_thread = new QThread(this);
        _thread ->setObjectName(QString::number(_s_handle,10));
        o_thread ->moveToThread(_thread);
        socket_thread_list.append(_thread);

        connect(d_thread,SIGNAL(data_produce(QByteArray)),o_thread,SLOT(writeContext(QByteArray)));

        connect(d_thread,SIGNAL(willClose_signals()),o_thread,SLOT(devWillClose_slots()));

        //connect(d_thread,SIGNAL(_error(QString)),o_thread,SLOT(get_error(QString)));
        connect(o_thread,SIGNAL(free_WriteThread(int)),d_thread,SLOT(_stop()));
        //connect(this,SIGNAL(_error(QString)),o_thread,SLOT(get_error(QString)));

        _thread ->start();

        if(d_thread ->get_client_number() == 0)
        {
            d_thread ->start();
        }
        d_thread ->add_C_N();



        emit _status_info(QTime::currentTime().toString()+QObject::trUtf8("_____设备_成功_______")+QString::number(_s_handle,10));

        emit clientDevInfo_signals(_s_handle,dev);
    }
}
void CameraServer::freeS_Thread(int id)
{
    QThread *_th;
    ServerSocketObject *S_o;
    for(int i = 0;i < socket_thread_list.size();++i)
    {
        _th = socket_thread_list.at(i);
        if(_th->objectName() == QString::number(id,10))
        {
            qDebug()<<"_th free";
            socket_thread_list.removeAt(i);
            _th ->quit();
            _th ->wait();
            break;
        }
    }
    for(int j = 0;j <socket_list.size();++j)
    {
        S_o = socket_list.at(j);
        if(S_o ->objectName() == QString::number(id,10))
        {
            qDebug()<<"S_o free";
            socket_list.at(j)->deleteLater();
            socket_list.removeAt(j);
        }
    }
    qDebug()<<"class CameraServer freeS_Thread";
    emit _status_info(QTime::currentTime().toString()+QObject::trUtf8("________断开________")+QString::number(id,10));

    emit clientThreadClose_signals(id);
}

void CameraServer::prepare_stop()
{
//    int i = socket_list.size();
//    for(int j = 0;j < i;++j)
//    {
//        socket_list.at(j)->mySignals(socket_list.at(j)->getSocketId());
//    }
    foreach (ServerSocketObject *t, socket_list) {
        t->socketClose();
    }
}

void CameraServer::unloadDev(const QString &name, int number)
{
    if (willUnloadDevname.isEmpty())
    {
        return;
    }
    if (number != 0) return;
    if (!willunloadDev.contains(name)) return;
    foreach (const QString &temp,willUnloadDevname)
    {
        if (temp == name)
        {
            foreach (CameraThread* t, dev_thread_list) {
                if (t->getDevName() == temp)
                {
                    t->deleteLater();
                    emit hasUnloadDev(temp);
                    dev_name_list.removeOne(temp);
                    willunloadDev.removeOne(name);
                    return;
                }
            }

        }

    }
}
void CameraServer::killClientThread(const QString &id)
{
    foreach (ServerSocketObject*temp, socket_list) {
        if (QString::number(temp->getSocketId(),10) == id)
        {
            temp->devWillClose_slots();
            return;
        }

    }
}
void CameraServer::killDevThread(const QString &name)
{

    foreach (CameraThread* t, dev_thread_list) {
        if (t->getDevName() == name)
        {
            if (t->get_client_number() == 0)
            {
                t->deleteLater();
                emit hasUnloadDev(name);
                dev_name_list.removeOne(name);
                dev_thread_list.removeOne(t);
                return;
            }
            willunloadDev.append(name);
            t->willclose();
            return;
        }
    }
}
void CameraServer::workClientCMD_slots(int cmd, const QString &argv, int handle)
{
    switch (cmd) {
    case 0:{
        ServerSocketObject *temp;
        temp = getServerSocket(handle);
        if (temp != NULL)
        {
            temp->writeContext(cmdLogFilesContext());
        }

    }   break;
    case 1:{
        ServerSocketObject *temp;
        temp = getServerSocket(handle);
        if (temp != NULL)
        {
            temp->writeContext(cmdLogFileContext(argv));
        }
    }break;
    case 2:{
        ServerSocketObject *temp;
        temp = getServerSocket(handle);
        if (temp != NULL)
        {
            temp->writeContext(cmdClientsContext());
        }
    }break;
    case 3:{
        ServerSocketObject *temp;
        temp = getServerSocket(handle);
        if (temp != NULL)
        {
            temp->writeContext(cmdDevsContext());
        }
    }break;
    case 4:{
        ServerSocketObject *temp;
        temp = getServerSocket(handle);
        if (temp != NULL)
        {
            temp->writeContext(cmdDevnamesContext());
        }
    }break;
    default:
        break;
    }
}
void CameraServer::clientInfoUpdate(int handle, const QString &info)
{
    if (info == "close") {
        clientsInfo.remove(handle);
        return;
    }
    if (clientsInfo.contains(handle)) {
        clientsInfo[handle] = info;
    } else {
        clientsInfo.insert(handle,info);
    }
}
void CameraServer::devInfoUpdate(const QString &name, const QString &info)
{
    if (info == "unload") {
        workingDevsInfo.remove(name);
        return;
    }
    if (workingDevsInfo.contains(name)) {
        workingDevsInfo[name] = info;
    } else {
        workingDevsInfo.insert(name,info);
    }
}

void CameraServer::clientClose_slots(int id)
{
    emit clientClose_signals(id,"close");
}
void CameraServer::devUnload_slots(const QString &name)
{
    emit devUnload_signals(name,"unload");
}

ServerSocketObject* CameraServer::getServerSocket(int handle)
{
    foreach (ServerSocketObject*temp, socket_list) {
        if (temp->getSocketId() == handle)
        {
            return temp;
        }

    }
    return NULL;
}
QByteArray CameraServer::cmdLogFilesContext()
{

    QDir Dir(dir);
    if (!Dir.exists())
    {
        qDebug() << Dir.mkdir(dir);
    }
    QByteArray buffer;

    QDataStream out(&buffer,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_6);

    out <<(int)0;
    out << 2;
    out << 0;//请求文件目录内容

    QStringList infolist = Dir.entryList(QStringList()<<tr("*.log"),QDir::Files,QDir::Name);
    QString t;
    foreach(QString temp,infolist)
    {
        t += temp.append('\n');
    }
    out<<t.toUtf8();
    out.device()->seek(0);
    out << (int)(buffer.size() - sizeof(int));

    return buffer;

}
QByteArray CameraServer::cmdLogFileContext(const QString &fileName)
{
    QFile file(dir+fileName);
    QByteArray buffer;
    QDataStream out(&buffer,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_6);

    out <<(int)0;
    out << 2;//cmd
    out << 1;//请求文件内容

    if (!file.open(QIODevice::ReadOnly))
    {

        out << "error!";

        out.device()->seek(0);

        out << (int)(buffer.size() - sizeof(int));

        return buffer;
    }

    out << file.readAll();

    out.device()->seek(0);

    out << (int)(buffer.size() - sizeof(int));

    return buffer;
}
QByteArray CameraServer::cmdClientsContext()
{
    QByteArray buffer;
    QDataStream out(&buffer,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_6);

    out <<(int)0;
    out << 2;
    out << 2;//请求现在链接服务器的客服段的内容
    QStringList l = clientsInfo.values();
    QString t;
    foreach (QString temp, l) {
        //out << temp.toUtf8().append('\n');
        t += temp.append('\n');
    }
    out << t.toUtf8();
    out.device()->seek(0);
    out << (int)(buffer.size() - sizeof(int));
    return buffer;
}
QByteArray CameraServer::cmdDevsContext()
{
    QByteArray buffer;
    QDataStream out(&buffer,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_6);

    out <<(int)0;
    out << 2;
    out << 3;//请求服务端现在设备运行情况
    QStringList l = workingDevsInfo.values();
    QString t;
    foreach (QString temp, l) {
        t += temp.append('\n');

    }
    out << t.toUtf8();
    out.device()->seek(0);
    out << (int)(buffer.size() - sizeof(int));
    return buffer;
}
QByteArray CameraServer::cmdDevnamesContext()
{
    QByteArray buffer;
    QDataStream out(&buffer,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_6);

    out <<(int)0;
    out << 2;
    out << 4;//请求文件名

    out <<devInfo;

    out.device()->seek(0);
    out << (int)(buffer.size() - sizeof(int));
    return buffer;
}
