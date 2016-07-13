/********************************************************************
* author 周翔
* e-mail 604487178@qq.com
* blog http://blog.csdn.net/zhx6044
**********************************************************************/

#include <QApplication>
#include "mainwindow.h"
#include "settingdialog.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //SettingDialog sd;

    MainWindow w;
    // QObject::connect(&sd,SIGNAL(sig_IpAndPort(QString,int)),&w,SLOT(slt_setIPandPort(QString,int)));
    // sd.show();
    // sd.exec();

    w.setAttribute(Qt::WA_AcceptTouchEvents);

    w.showFullScreen();
   // w.show();
    return a.exec();
}
