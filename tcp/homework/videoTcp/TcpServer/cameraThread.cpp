#include "cameraThread.h"

#include "cameraV4L2.h"
#include "ServerSocket.h"
#include "CommandType.h"
#include "YUYVtoRGB.h"

#include <QDebug>

CameraThread::CameraThread(QObject *parent, const QString &file_name):QThread(parent),
    flag(true),
    dev_status(false),
    dev_name (file_name),
    client_number(0)
{
    this ->setObjectName(dev_name);
    connect(this,SIGNAL(dev_init_fail(int)),this,SLOT(free_dev(int)));
    pp = new uchar[640*480*3*sizeof(char)];
    frame = new QImage(pp,640,480,QImage::Format_RGB888);

}
CameraThread::~CameraThread()
{
    qDebug()<<"dev_thread~~~~~~~~~~~~~~";
    delete frame;
    delete pp;
}
void CameraThread::run()//设备数据产生
{
    if(!dev_status)
    {
        vd = new cameraV4L2(dev_name);
        if(int i = vd ->init() != 0)
        {
            emit dev_init_fail(i);
            emit _error("dev init fail!");
            return;
        }

        dev_status = true;
    }
    mutex.lock();
    while(flag)
    {
        mutex.unlock();
        pFrameData = vd->getFrameData();
        convert_yuv_to_rgb_buffer(pFrameData,pp,640,480);
        frame->loadFromData(pp,640 * 480 * 3 * sizeof(char));

   //     qDebug()<<frame->format();

        QByteArray frameArray;
        QBuffer buffer(&frameArray);
        buffer.open(QIODevice::WriteOnly);
        frame->save(&buffer,"JPEG");
        //本来想使用xvid进行无损压缩，可是一直调试出错，改为使用Qt的图片save函数，通过图片格式的转换来间接实现的有损压缩

        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_4_6);
        out<<(int)0;
        out<<isCam;
        out<<frameArray;
        out.device()->seek(0);
        out<< (int)(block.size()-sizeof(int));
        emit data_produce(block);
    //    qDebug()<<frameArray.size();
        vd->unget_frame();
        msleep(33);
    }

}
void CameraThread::_stop()//终止循环
{

    mutex_cN.lock();
    --client_number;
    mutex_cN.unlock();
    if(client_number == 0)
    {
        mutex.lock();
        flag = false;
        mutex.unlock();
        wait();
        qDebug()<<"class CameraThread _stop";
        if(dev_status)
        {
            __exit();
            qDebug()<<"class dev_free";
        }
    }
    emit clientNumber_Signals(dev_name,client_number);
}
void CameraThread::__exit()//释放设备
{   
    vd ->freeDev();
    dev_status = false;
    flag = true;
    qDebug()<<"class CameraThread __exit";
}
void CameraThread::free_dev(int i)
{
    switch(i)
    {
    case 3:vd ->uninit_device();
    case 2:vd ->close_device();
    case 1:;
    }

}
int CameraThread::get_client_number()
{
    int i;
    mutex_cN.lock();
    i = this ->client_number;
    mutex_cN.unlock();
    return i;
}
void CameraThread::add_C_N()
{
    mutex_cN.lock();
    ++client_number;
    mutex_cN.unlock();
    emit clientNumber_Signals(dev_name,client_number);
}
