#include "cameraV4L2.h"
#include <QDebug>
cameraV4L2::cameraV4L2(const QString &file_name, int cameraFormat) :
    dev_name(file_name),
    fd(-1),
    buffers(NULL),
    n_buffers(0),
    index(-1),
    format(cameraFormat)
{
}
cameraV4L2::~cameraV4L2()
{
    this->stop_capturing();
    this->uninit_device();
    this->close_device();
    qDebug()<<"~~~~~";
}
void cameraV4L2::freeDev()
{
    this->stop_capturing();
    this->uninit_device();
    this->close_device();
    qDebug()<<"~~~~~";
}
int cameraV4L2::init()
{
    if(-1 == this ->open_device())
    {
        qDebug()<<"open device fail!";
        return 1;
    }
    if(-1 == this ->init_device())
    {
        qDebug()<<"init device fail!";
        return 2;
    }
    if(-1 == this ->start_capturing())
    {
        qDebug()<<"start capturing fail!";
        return 3;
    }
    return 0;
}
int cameraV4L2::open_device()//打开设备
{
    fd = open(dev_name.toStdString().c_str(), O_RDWR/*|O_NONBLOCK*/, 0);
    // fd = open(dev_name.toStdString().c_str(), O_RDWR|O_NONBLOCK, 0);
    if(-1 == fd)
    {
        emit display_error(QObject::trUtf8("open: %1").arg(QString(strerror(errno))));
        return -1;
    }
    return 0;
}
int cameraV4L2::close_device()//关闭设备
{
    if(-1 == close(fd))
    {
        emit display_error(QObject::trUtf8("close: %1").arg(QString(strerror(errno))));
        return -1;
    }
    //free(pp);
    return 0;
}
int cameraV4L2::init_device()//初始化设备
{
    v4l2_capability cap;//性能
    v4l2_cropcap cropcap;
    v4l2_crop crop;
    v4l2_format fmt;//帧格式

    if(-1 == ioctl(fd, VIDIOC_QUERYCAP, &cap))//是否是V4l2设备，设备信息放入cap中
    {
        if(EINVAL == errno)
        {
            emit display_error(QObject::trUtf8("%1 is no V4l2 device").arg(dev_name));
        }
        else
        {
            emit display_error(QObject::trUtf8("VIDIOC_QUERYCAP: %1").arg(QString(strerror(errno))));
        }
        return -1;
    }

    if(!(cap.capabilities & V4L2_CAP_VIDEO_CAPTURE))/* Is a video capture device */
    {
        emit display_error(QObject::trUtf8("%1 is no video capture device").arg(dev_name));
        return -1;
    }

    if(!(cap.capabilities & V4L2_CAP_STREAMING))//设备是否支持数据流
    {
        emit display_error(QObject::trUtf8("%1 does not support streaming i/o").arg(dev_name));
        return -1;
    }

    CLEAR(cropcap);

    cropcap.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

    if(0 == ioctl(fd, VIDIOC_CROPCAP, &cropcap))
    {
        CLEAR(crop);
        crop.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        crop.c = cropcap.defrect;

        if(-1 == ioctl(fd, VIDIOC_S_CROP, &crop))
        {
            if(EINVAL == errno)
            {
                //emit display_error(tr("VIDIOC_S_CROP not supported"));
            }
            else
            {
                qDebug() << strerror(errno);
                emit display_error(QObject::trUtf8("VIDIOC_S_CROP: %1").arg(QString(strerror(errno))));
            }
        }
    }
    else
    {
        emit display_error(QObject::trUtf8("VIDIOC_CROPCAP: %1").arg(QString(strerror(errno))));
        return -1;
    }
    //此处查询设备信息，一个设备类有一个帧格式链表，存放此设备所支持的所有帧格式
    /*******************************/
//    struct v4l2_fmtdesc fmt1;
//    int ret;
//    memset(&fmt1, 0, sizeof(fmt1));
//    fmt1.index = 0;
//    fmt1.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

//    while ((ret = ioctl(fd, VIDIOC_ENUM_FMT, &fmt1)) == 0)//显示所有支持的格式；
//    {
//        ++fmt1.index;
//        qDebug()<<"pixelformat ="<<char(fmt1.pixelformat & 0xFF)<<char((fmt1.pixelformat >> 8) & 0xFF)
//               <<char((fmt1.pixelformat >> 16) & 0xFF)<<char((fmt1.pixelformat >> 24) & 0xFF);
//        QString a;
//        a.append(char(fmt1.pixelformat & 0xFF));
//        a.append(char((fmt1.pixelformat >> 8) & 0xFF));
//        a.append(char((fmt1.pixelformat >> 16) & 0xFF));
//        a.append(char((fmt1.pixelformat >> 24) & 0xFF));
//        format_list.append(a);
//    }
    /*********************************/

    CLEAR(fmt);
    //  if(format_list.contains("YUYV"));
    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    fmt.fmt.pix.width = 640;
    fmt.fmt.pix.height = 480;
    fmt.fmt.pix.pixelformat = format/*V4L2_PIX_FMT_YUYV*/;
    fmt.fmt.pix.field = V4L2_FIELD_INTERLACED;/* both fields interlaced */

    if(-1 == ioctl(fd, VIDIOC_S_FMT, &fmt))
    {
        emit display_error(QObject::trUtf8("VIDIOC_S_FMT").arg(QString(strerror(errno))));
        return -1;
    }

    if(-1 == init_mmap())
    {
        return -1;
    }

    return 0;

}
int cameraV4L2::init_mmap()//初始化内存映射
{
    v4l2_requestbuffers req;//向系统申请帧缓冲的请求，包括申请的个数
    CLEAR(req);

    req.count = 4;
    req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory = V4L2_MEMORY_MMAP;

    if(-1 == ioctl(fd, VIDIOC_REQBUFS, &req))
    {
        if(EINVAL == errno)
        {
            emit display_error(QObject::trUtf8("%1 does not support memory mapping").arg(dev_name));
            return -1;
        }
        else
        {
            emit display_error(QObject::trUtf8("VIDIOC_REQBUFS %1").arg(QString(strerror(errno))));
            return -1;
        }
    }

    if(req.count < 2)
    {
        emit display_error(QObject::trUtf8("Insufficient buffer memory on %1").arg(dev_name));
        return -1;
    }

    buffers = (buffer*)calloc(req.count, sizeof(*buffers));

    if(!buffers)
    {
        emit display_error(QObject::trUtf8("out of memory"));
        return -1;
    }

    for(n_buffers = 0; n_buffers < req.count; ++n_buffers)//
    {
        v4l2_buffer buf;//驱动中的一帧
        CLEAR(buf);

        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        buf.index = n_buffers;

        if(-1 == ioctl(fd, VIDIOC_QUERYBUF, &buf))
        {
            emit display_error(QObject::trUtf8("VIDIOC_QUERYBUF: %1").arg(QString(strerror(errno))));
            return -1;
        }
        /*建立驱动缓冲到内存的映射*/
        buffers[n_buffers].length = buf.length;
        buffers[n_buffers].start = //建立内存映射
                mmap(NULL, // start anywhere
                     buf.length,
                     PROT_READ | PROT_WRITE,
                     MAP_SHARED,
                     fd, buf.m.offset);

        if(MAP_FAILED == buffers[n_buffers].start)//映射失败
        {
            emit display_error(QObject::trUtf8("mmap %1").arg(QString(strerror(errno))));
            return -1;
        }
    }
    return 0;
}
int cameraV4L2::start_capturing()
{
    unsigned int i;
    for(i = 0; i < n_buffers; ++i)
    {
        v4l2_buffer buf;
        CLEAR(buf);

        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory =V4L2_MEMORY_MMAP;
        buf.index = i;
        //        fprintf(stderr, "n_buffers: %d\n", i);

        if(-1 == ioctl(fd, VIDIOC_QBUF, &buf))
        {
            emit display_error(QObject::trUtf8("VIDIOC_QBUF: %1").arg(QString(strerror(errno))));
            return -1;
        }
    }

    v4l2_buf_type type;
    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

    if(-1 == ioctl(fd, VIDIOC_STREAMON, &type))
    {
        emit display_error(QObject::trUtf8("VIDIOC_STREAMON: %1").arg(QString(strerror(errno))));
        return -1;
    }
    return 0;
}
int cameraV4L2::stop_capturing()
{
    v4l2_buf_type type;
    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

    if(-1 == ioctl(fd, VIDIOC_STREAMOFF, &type))
    {
        emit display_error(QObject::trUtf8("VIDIOC_STREAMOFF: %1").arg(QString(strerror(errno))));
        return -1;
    }
    return 0;

}
int cameraV4L2::uninit_device()
{
    unsigned int i;
    for(i = 0; i < n_buffers; ++i)
    {
        if(-1 == munmap(buffers[i].start, buffers[i].length))
        {
            emit display_error(QObject::trUtf8("munmap: %1").arg(QString(strerror(errno))));
            return -1;
        }

    }
    free(buffers);
    return 0;

}

int cameraV4L2::get_frame(void **frame_buf, size_t *len)
{
    v4l2_buffer queue_buf;
    CLEAR(queue_buf);

    queue_buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    queue_buf.memory = V4L2_MEMORY_MMAP;

    if(-1 == ioctl(fd, VIDIOC_DQBUF, &queue_buf))
    {
        switch(errno)
        {
        case EAGAIN:
            return -1;
        case EIO:
            return -1 ;
        default:
            emit display_error(QObject::trUtf8("VIDIOC_DQBUF: %1").arg(QString(strerror(errno))));
            return -1;
        }
    }

    *frame_buf = buffers[queue_buf.index].start;
    *len = buffers[queue_buf.index].length;
    index = queue_buf.index;

    return 0;
}
int cameraV4L2::unget_frame()
{
    if(index != -1)
    {
        v4l2_buffer queue_buf;
        CLEAR(queue_buf);

        queue_buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        queue_buf.memory = V4L2_MEMORY_MMAP;
        queue_buf.index = index;

        if(-1 == ioctl(fd, VIDIOC_QBUF, &queue_buf))
        {
            emit display_error(QObject::trUtf8("VIDIOC_QBUF: %1").arg(QString(strerror(errno))));
            return -1;
        }
        return 0;
    }
    return -1;
}
uchar* cameraV4L2::getFrameData()
{
    size_t len;
    this->get_frame((void**)&p,&len);
    return p;
}
