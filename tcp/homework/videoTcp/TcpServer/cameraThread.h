#ifndef CAMERATHREAD_H
#define CAMERATHREAD_H

#include <QThread>
#include <QMutex>
#include <QBuffer>
#include <QImage>


#include <QDebug>


class cameraV4L2;
class ServerSocket;

class CameraThread : public QThread
{
    Q_OBJECT
public:
    CameraThread(QObject *parent = 0,const QString& file_name = "");
    ~CameraThread();
    int get_client_number();
    void add_C_N();
    void willclose() {emit willClose_signals(); }
    QString getDevName()const {return dev_name;}
signals:
    void data_produce(const QByteArray&);
    void __status_info(const QString&);
    void dev_init_fail(int);
    void _error(const QString&);

    void clientNumber_Signals(const QString&,int);

    void willClose_signals();
public slots:
    void _stop();
protected slots:
    void run();
    void __exit();
    void free_dev(int);
private:
    cameraV4L2 *vd;
    volatile bool flag;
    volatile bool dev_status;
    QString dev_name;
    QMutex mutex;
    ServerSocket *workSocket;
    QImage image;
    volatile int client_number;//此设备进程的客户连接数
    QMutex mutex_cN;
    uchar* pFrameData;
    uchar *pp;
    QImage *frame;
};

#endif // CAMERATHREAD_H
