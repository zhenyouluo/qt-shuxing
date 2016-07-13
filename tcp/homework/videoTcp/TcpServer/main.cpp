/**************************************************************************
  * author ZhouXiang
  * Copyright
  * Version 1.0
  * funtion 一个设备一次为一个客户提供视频服务，设备数据产生在独立线程中，设备线程在开始初始化时产生后放进线程池中，有外部连接的
  *         时创建一个线程在此线程中将设备产生的数据发送到客户端。
  *         客服端与服务端连接断开，服务端socket线程释放。
  *
  ************************************************************************/
#include <QtGui>
#include<QApplication>
//#include "serverwidget.h"
#include "servermainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ServerMainWindow w;
    w.showMaximized();
    return a.exec();
}
