#include <QApplication>

#include "inputadminpassworddialog.h"
#include "clientmainwindow.h"

int main(int argc,char* argv[])
{
    QApplication a(argc,argv);

    ClientMainWindow w;
    InputAdminPasswordDialog dialog;
    QObject::connect(&dialog,SIGNAL(adminInfo_signals(QString,QString)),&w,SLOT(writeAdminNamePassWord(QString,QString)));
    QObject::connect(&dialog,SIGNAL(sig_IpAndPort(QString,int)),&w,SLOT(setIPandPort(QString,int)));
    QObject::connect(&w,SIGNAL(adminLoginResult_signals()),&dialog,SLOT(close()));
    QObject::connect(&w,SIGNAL(sig_loginError()),&dialog,SLOT(slt_loginError()));
    QObject::connect(&w,SIGNAL(connectError()),&dialog,SLOT(slt_connectError()));
    QObject::connect(&dialog,SIGNAL(sig_quit()),&a,SLOT(quit()));
    dialog.show();

    return a.exec();

}
