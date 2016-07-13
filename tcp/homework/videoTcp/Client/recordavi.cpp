#include "recordavi.h"

#include <QDebug>

RecordAVI::RecordAVI(QObject *parent) :
    QObject(parent)
{
    int isColor = 1;
    int fps     = 15; // or 25
    int frameW = 640; // 744 for firewire cameras
    int frameH = 480; // 480 for firewire cameras
    writer=cvCreateVideoWriter((QDate::currentDate().toString("dd.MM.yyyy")+";"+QTime::currentTime().toString("h:m:s ap")+".avi").toLatin1().data(),CV_FOURCC('M','J','P','G'),
                               fps,cvSize(frameW,frameH),isColor);
    if(!writer)
    {
        qDebug()<<"writer error!";
    }
}
RecordAVI::~RecordAVI()
{
    cvReleaseImage(&frame);
    cvReleaseVideoWriter(&writer);
    qDebug()<<"AVI~~~~~~~~~~~~~";
}
void RecordAVI::getImage(const QImage &im)
{
    im.save("a.jpg");
    frame = cvLoadImage("a.jpg",1);
    int n = cvWriteFrame(writer,frame);
    if(n != 1)
    {
        cvReleaseImage(&frame);
        emit _error();
    }
    cvReleaseImage(&frame);
    //  qDebug()<<QThread::currentThreadId();
}
