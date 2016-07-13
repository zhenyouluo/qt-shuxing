#include "widget.h"

#include <QtGui>
#include <QApplication>
int ui_start()
{

    int argc = 0;
    QApplication app(argc, 0);
    Widget *widget = new Widget;
    widget->show();
    //widget->showFullScreen();
    app.exec();
    widget->StopThread();
    return 0;
}
