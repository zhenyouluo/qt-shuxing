/********************************************
  * 下面要做的工作：1.读出设备所支持的帧格式化
  *              2.默认的帧格式设置为YUYV，不支持则更换，转换算法也必须跟着换
  *              3.提高稳定性，实现效率的优化
  *******************************************/
#ifndef CAMERAV4L2_H
#define CAMERAV4L2_H

#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>


#include <sys/ioctl.h>
#include <sys/mman.h>

#include <asm/types.h>
#include <linux/videodev2.h>

#include <QString>
#include <QObject>


#define CLEAR(x) memset(&(x), 0, sizeof(x))


class cameraV4L2 : public QObject
{
    Q_OBJECT
public:
    explicit cameraV4L2(const QString& file_name = QString(),int cameraFormat = V4L2_PIX_FMT_YUYV);
    ~cameraV4L2();
    int init();
    void freeDev();
    int uninit_device();
    int close_device();
    int unget_frame();
    uchar* getFrameData();
signals:
    void display_error(const QString&);
public slots:

private:
    int init_mmap();
    int open_device();
    int init_device();
    int start_capturing();
    int stop_capturing();
    int get_frame(void **, size_t*);
    struct buffer
    {
        void * start;
        size_t length;
    };
    QString dev_name;
    int fd;
    buffer* buffers;
    unsigned int n_buffers;
    int index;
    uchar *p;
    //  QImage *frame;
    //__u32 NowFormat;//用来标志帧格式
    //  QStringList format_list;
    int format;



};

#endif // CAMERAV4L2_H
