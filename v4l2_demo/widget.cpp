#include "widget.h"
#include "queue.h"
#include "convert.h"
#include "drawRect.h"
#include "TextureAS.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <math.h>
#include<iostream>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/videodev2.h>
using  namespace std;

void *curr_data = 0;
int curr_len = 0;
pthread_mutex_t  curr_lock = PTHREAD_MUTEX_INITIALIZER;

static void curr_data_set(void *data, int len) {
    pthread_mutex_lock(&curr_lock);
    if(curr_data != NULL) {
        free(curr_data);
        curr_data = NULL;
    }
    curr_data = data;
    curr_len = len;
    pthread_mutex_unlock(&curr_lock);
}

static void curr_data_get(void **data, int *len) {

    pthread_mutex_lock(&curr_lock);
    if(curr_data != NULL) {
        *len = curr_len;
        unsigned char *p = (unsigned char *)malloc(curr_len);
        memcpy(p, curr_data, curr_len);
        *data = p;
    }
    pthread_mutex_unlock(&curr_lock);
}
struct timeval tv1, tv2;

QString time_a,time_b;
Widget::Widget()
{
    myThread = new Thread;
    QVBoxLayout *layout = new QVBoxLayout;

    QGraphicsScene *scene = new QGraphicsScene;
    QGraphicsView *view = new QGraphicsView(scene);
    QPushButton *btn_cap = new QPushButton("cap");
   live_time=new QLineEdit ();
   live_time2=new QLineEdit();
 //live_time->setText(QString (time_a));
    btn_cap->setFixedSize(40, 30);

    scene->addItem(&item);

    layout->addWidget(view);
    layout->addWidget(btn_cap);
     layout->addWidget(live_time);
     layout->addWidget(live_time2);

    setLayout(layout);

    connect(myThread, SIGNAL(ImageSignal()), this, SLOT(ImageSlot()));
    connect(btn_cap, SIGNAL(clicked()), this, SLOT(ImageCap()));
    setWindowTitle("webcam Test");
    setFixedSize(640 + 25, 480 + 25 + 30 + 10);
    myThread->start();

    option = new QAction("Option", this);
   // option_live=new QAction("live_time",this);
    addAction(option);
    //addAction(option_live);
    setContextMenuPolicy(Qt::ActionsContextMenu);
    connect(option, SIGNAL(triggered()), this, SLOT(OptionClicked()));
    bgr_data = NULL;
}

Widget::~Widget() {}

 HTAS htas1 = TAS_Create("TC1.dat","TT.bmd", "quality");

void Widget::RefreshImage(const void *buf, int len)
{

    if(buf == NULL || len <= 0) return;

    int width, height;

    if(mjpeg_info((unsigned char *)buf, len, &width, &height) < 0) { //jpg fomat error
        return;
    }

    if(width*height > 1920*1080) { //max 1080p
        return;
    }
    if(bgr_data == NULL)
        bgr_data = (unsigned char *)malloc(width*height*3);
        //time_all=(char*)malloc(1024);
    gettimeofday (&tv1, NULL);
 mjpeg2bgr((unsigned char *)buf, len, bgr_data, width*height*3);
 /*****************************************/
 gettimeofday(&tv2, NULL);
 time_a.sprintf("图片转换时间: %dms",(tv2.tv_sec - tv1.tv_sec)*1000 + (tv2.tv_usec - tv1.tv_usec)/1000);
live_time->setText(QString (time_a));

 TLiveness red_live[10];
 gettimeofday (&tv1, NULL);
 int red_count = TAS_Detect(htas1, (unsigned char*)bgr_data,  width, height,width*3, 10,red_live);

      //printf("====================TAS_Detect1 time: %ldms\n", (tv2.tv_sec - tv1.tv_sec)*1000 + (tv2.tv_usec - tv1.tv_usec)/1000);

    //  cout<<"asdasd"<<red_count<<endl;
      if(red_count!=0){
          gettimeofday(&tv2, NULL);
          time_b.sprintf("活体识别时间: %dms 比分:%f",(tv2.tv_sec - tv1.tv_sec)*1000 + (tv2.tv_usec - tv1.tv_usec)/1000,red_live[0].score);
         live_time2->setText(QString (time_b));
          cout << red_live[0].ptEyes[0].x << " " << red_live[0].ptEyes[0].y <<endl;
          cout<<red_live[0].rtFace.left<<" "<<red_live[0].rtFace.right<<" "<<red_live[0].rtFace.top<<" "<<red_live[0].rtFace.bottom<<endl;
           drawRectangle(bgr_data, width, height, int(red_live[0].rtFace.left),int(red_live[0].rtFace.top+10) ,int(red_live[0].rtFace.right) ,int( red_live[0].rtFace.bottom));
            //drawRectangle((unsigned char* )bgr_data,240,240,10,10,10,10);

      }
      else
          live_time2->setText(" ");


      /*******************************************/



    QPixmap pix = QPixmap::fromImage(QImage((unsigned char *)bgr_data, width, height, QImage::Format_RGB888));




    item.setPixmap(pix);
   // free(bgr_data);
}



void Widget::ImageSlot()
{
    void *data;
    int len;
    while(1) {
        data = NULL;
        queue_pop(&data, &len);
        if(data == NULL) break;
        RefreshImage(data, len);
        curr_data_set(data, len);
        //queue_elem_free((void **)&data);
    }
}

void Widget::ImageCap() {
    void *data = NULL;
    int len;
    curr_data_get(&data, &len);
    if(data != NULL) {
        int fd = open("a.jpg", O_CREAT | O_WRONLY, 0644);
        if(fd >= 0) {
            write(fd, data, len);
            ::close(fd);
        }
        free(data);
    }
}

void Widget::OptionClicked() {
    printf("Option clicked\n");
}

void Widget::StopThread(void)
{
    myThread->SetStop();
    usleep(Thread_SLEEP_MS * 1000);
    myThread->terminate();
}
