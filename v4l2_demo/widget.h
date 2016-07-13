#ifndef WIDGET_H_
#define WIDGET_H_

#include "thread.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QAction>
#include<QTextEdit>
#include<QLineEdit>

class Widget : public QWidget
{ 
    Q_OBJECT
private: 
    Thread *myThread; 
    QGraphicsPixmapItem item;
    QAction *option;
    QLineEdit *live_time,*live_time2;
    unsigned char *bgr_data;
    void RefreshImage(const void *buf, int len);
public: 
    Widget();
    ~Widget();
    void StopThread(void);
public slots:
    void ImageSlot();
    void OptionClicked();
    void ImageCap();
};

#endif
