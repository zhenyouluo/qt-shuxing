#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/videodev2.h>
#include <time.h>
#include <math.h>
#include<iostream>

#include "queue.h"
#include "capture.h"
#include "ui.h"
#include "convert.h"
#include "TextureAS.h"

using  namespace std;
#define CLEAR(x) memset(&(x), 0, sizeof(x))

#define CAPUTRE_MAX_IDX 32
#define CAPUTRE_DEFAULT_FPS 15
#define BUFFER_REQ_NUM 4
#define CAPUTRE_DEV_FMT "/dev/video%d"
pthread_mutex_t cap_mutex = PTHREAD_MUTEX_INITIALIZER;
int dev_idx = 0;

struct buffer {
    void   *start;
    size_t  length;
};

typedef struct {
    int fd;
    int stop_flag;
    int width;
    int height;
    int fps;
    char dev_name[32];
    struct buffer buffers[BUFFER_REQ_NUM];
    int n_buffers;
    pthread_t cap_thread;
    void *callback;
} capture_handle_t;

void destroy_capture(capture_handle_t **handle);
#define errno_return(s) do \
{ \
    fprintf(stderr, "%s error %d, %s\n", s, errno, strerror(errno)); \
    return -1; \
} while(0)

static int xioctl(int fh, int request, void *arg)
{
    int r;
    do {
        r = ioctl(fh, request, arg);
    } while (-1 == r && EINTR == errno);

    return r;
}

// struct timeval tv1, tv2;
int read_frame(capture_handle_t *handle)
{
    // gettimeofday(&tv1, NULL);
    // printf("diff %dms\n", (tv1.tv_sec-tv2.tv_sec)*1000 + (tv1.tv_usec-tv2.tv_usec)/1000);
    // tv2 = tv1;
    struct v4l2_buffer buf;

    CLEAR(buf);
    buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory = V4L2_MEMORY_MMAP;

    if (-1 == xioctl(handle->fd, VIDIOC_DQBUF, &buf)) {
        return -1;
    }
    callback_func func = (callback_func)handle->callback;
    if(func != NULL) {

        func(handle->buffers[buf.index].start, buf.bytesused);
        //mjpeg_info(handle->buffers[buf.index].start, buf.bytesused, handl->width, &height);
//        unsigned char *image1 = (unsigned char *)malloc((handle-> width)* (handle-> height)*3);
//        mjpeg2bgr((unsigned char*)handle->buffers[buf.index].start,buf.bytesused , image1, (handle->width)*(handle->height)*3);
//         HTAS htas1 = TAS_Create("TC1.dat","TT.bmd", "quality");
//        TLiveness red_live[10];
//        gettimeofday(&tv1, NULL);
//        int red_count = TAS_Detect(htas1, (unsigned char*)image1, handle-> width, handle-> height,handle-> width*3, 10, red_live);

//                     //      red_live[]
        //    gettimeofday(&tv2, NULL);
//             printf("====================TAS_Detect1 time: %ldms\n", (tv2.tv_sec - tv1.tv_sec)*1000 + (tv2.tv_usec - tv1.tv_usec)/1000);
//             cout<<"asdasd"<<red_count<<endl;
//             //func(image1, buf.bytesused);

//            free( image1 );
    }
    xioctl(handle->fd, VIDIOC_QBUF, &buf);

    return 0;
}

static void* caploop(__attribute__((unused)) void *arg)
{
    capture_handle_t *handle = (capture_handle_t *)arg;
    for (;;) {
        fd_set fds;
        struct timeval tv;
        int r;

        FD_ZERO(&fds);
        FD_SET(handle->fd, &fds);

        /* Timeout. */
        tv.tv_sec = 2;
        tv.tv_usec = 0;

        if(handle->stop_flag) break;
        r = select(handle->fd + 1, &fds, NULL, NULL, &tv);
        if(handle->stop_flag) break;
        if (r < 0) {
            destroy_capture(&handle);
            break;
        }
        if (0 == r) {
            fprintf(stderr, "select timeout\n");
            continue;
        }
        if(read_frame(handle) < 0) {
            destroy_capture(&handle);
            break;
        }
    }    
    return NULL;
}

static void stop_capturing(capture_handle_t *handle)
{
    enum v4l2_buf_type type;
    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    handle->stop_flag = 1;
    xioctl(handle->fd, VIDIOC_STREAMOFF, &type);
}

static int start_capturing(capture_handle_t *handle)
{
    int i;
    enum v4l2_buf_type type;

    for (i = 0; i < handle->n_buffers; ++i) {
        struct v4l2_buffer buf;

        CLEAR(buf);
        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        buf.index = i;

        if (-1 == xioctl(handle->fd, VIDIOC_QBUF, &buf)) {
            errno_return("VIDIOC_QBUF");
        }
    }
    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if (-1 == xioctl(handle->fd, VIDIOC_STREAMON, &type)) {
        errno_return("VIDIOC_STREAMON");
    }
    handle->stop_flag = 0;
    //caploop(handle);
    pthread_create(&handle->cap_thread, NULL, caploop, (void *)handle);
    pthread_detach(handle->cap_thread);
    return 0;
}

static void uninit_device(capture_handle_t *handle)
{
    int i;

    for (i = 0; i < handle->n_buffers; ++i)
        munmap(handle->buffers[i].start, handle->buffers[i].length);
}

static int init_mmap(capture_handle_t *handle)
{
    struct v4l2_requestbuffers req;

    CLEAR(req);

    req.count = BUFFER_REQ_NUM;
    req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory = V4L2_MEMORY_MMAP;

    if (-1 == xioctl(handle->fd, VIDIOC_REQBUFS, &req)) {
        if (EINVAL == errno) {
            fprintf(stderr, "%s does not support memory mapping\n", handle->dev_name);
            return -1;
        } else {
            errno_return("VIDIOC_REQBUFS");
        }
    }

    if (req.count < 2 || req.count > BUFFER_REQ_NUM) {
        fprintf(stderr, "Insufficient buffer memory on %s\n", handle->dev_name);
        return -1;
    }

    for (handle->n_buffers = 0; handle->n_buffers < (int)req.count; ++(handle->n_buffers)) {
        struct v4l2_buffer buf;

        CLEAR(buf);

        buf.type        = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory      = V4L2_MEMORY_MMAP;
        buf.index       = handle->n_buffers;

        if (-1 == xioctl(handle->fd, VIDIOC_QUERYBUF, &buf))
            errno_return("VIDIOC_QUERYBUF");

        handle->buffers[handle->n_buffers].length = buf.length;
        handle->buffers[handle->n_buffers].start =
        mmap(NULL /* start anywhere */,
              buf.length,
              PROT_READ | PROT_WRITE /* required */,
              MAP_SHARED /* recommended */,
              handle->fd, buf.m.offset);
        if(MAP_FAILED == handle->buffers[handle->n_buffers].start)
            errno_return("mmap");
    }
    return 0;
}

static int getFrameSize(int fd, int index, unsigned int code, int frameSize[6])
{
  struct v4l2_frmsizeenum vfse;
  CLEAR(vfse);
  vfse.index = index;
  vfse.pixel_format = code;

  int res = xioctl(fd, VIDIOC_ENUM_FRAMESIZES, &vfse);

  if (res < 0) { return res; }

  switch(vfse.type) {
  case V4L2_FRMSIZE_TYPE_DISCRETE:
    frameSize[0] = vfse.discrete.width;
    frameSize[1] = vfse.discrete.width;
    frameSize[2] = 0;
    frameSize[3] = vfse.discrete.height;
    frameSize[4] = vfse.discrete.height;
    frameSize[5] = 0;
    return res;

  case V4L2_FRMSIZE_TYPE_CONTINUOUS:
  case V4L2_FRMSIZE_TYPE_STEPWISE:
    frameSize[0] = vfse.stepwise.min_width;
    frameSize[1] = vfse.stepwise.max_width;
    frameSize[2] = vfse.stepwise.step_width;
    frameSize[3] = vfse.stepwise.min_height;
    frameSize[4] = vfse.stepwise.max_height;
    frameSize[5] = vfse.stepwise.step_height;
    return res;
  }

  return res;
}

//get max width and height
static void get_max_width_height(int fd, unsigned int code, int *width, int *height) {
    int r = 0, i = 0;
    int max_width = 0, max_height = 0;
    int frameSize[6] = {};
    do {
        r = getFrameSize(fd, i, code, frameSize);

        if(max_width*max_height < frameSize[1]*frameSize[4]) {
            max_width = frameSize[1];
            max_height = frameSize[4];
        }
        ++i;
    } while(r >= 0);
    *width = max_width;
    *height = max_height;
}

static int init_device(capture_handle_t *handle)
{
    struct v4l2_capability cap;
    struct v4l2_cropcap cropcap;
    struct v4l2_crop crop;
    struct v4l2_format fmt;
    unsigned int min;

    if (-1 == xioctl(handle->fd, VIDIOC_QUERYCAP, &cap)) {
        if (EINVAL == errno) {
            fprintf(stderr, "%s is no V4L2 device\n", handle->dev_name);
            return -1;
        } else {
            errno_return("VIDIOC_QUERYCAP");
        }
    }

    if (!(cap.capabilities & V4L2_CAP_VIDEO_CAPTURE)) {
        fprintf(stderr, "%s is no video capture device\n", handle->dev_name);
        return -1;
    }


    if (!(cap.capabilities & V4L2_CAP_STREAMING)) {
        fprintf(stderr, "%s does not support streaming i/o\n", handle->dev_name);
        return -1;
    }



    CLEAR(cropcap);
    cropcap.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if (0 == xioctl(handle->fd, VIDIOC_CROPCAP, &cropcap)) {
        crop.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        crop.c = cropcap.defrect; /* reset to default */
        xioctl(handle->fd, VIDIOC_S_CROP, &crop);
    }

    CLEAR(fmt);

    get_max_width_height(handle->fd, V4L2_PIX_FMT_MJPEG, &handle->width, &handle->height);
    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    
    fmt.fmt.pix.width       = handle->width;
    fmt.fmt.pix.height      = handle->height;
    fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_MJPEG;
    fmt.fmt.pix.field       = V4L2_FIELD_NONE;

    if (-1 == xioctl(handle->fd, VIDIOC_S_FMT, &fmt)) {
        errno_return("VIDIOC_S_FMT");
    }
    if(fmt.fmt.pix.pixelformat != V4L2_PIX_FMT_MJPEG) {
        printf("device %s not support MJPEG format\n", handle->dev_name);
        return -1;
    }
    handle->width = fmt.fmt.pix.width;
    handle->height = fmt.fmt.pix.height;
    printf("format: %dx%d MJPEG\n", fmt.fmt.pix.width, fmt.fmt.pix.height);

    //set fps to 15
    struct v4l2_streamparm fpsparam;
    struct v4l2_fract *tpf;
    memset (&fpsparam, 0, sizeof (fpsparam));
    fpsparam.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    tpf = &fpsparam.parm.capture.timeperframe;
    tpf->numerator = 1;
    tpf->denominator = CAPUTRE_DEFAULT_FPS;
    if(-1 == xioctl(handle->fd, VIDIOC_S_PARM, &fpsparam)) {
        errno_return("VIDIOC_S_PARM");
    }
    handle->fps = tpf->denominator;
    printf("fps: %d\n", tpf->denominator);

    struct v4l2_queryctrl  setting;
    setting.id = V4L2_CID_EXPOSURE_AUTO;
    int ret = xioctl(handle->fd, VIDIOC_QUERYCTRL, &setting);
    printf("name: %s min: %d max: %d stp: %d def: %d\n", setting.name, setting.minimum, setting.maximum, setting.step, setting.default_value);

    setting.id = V4L2_CID_EXPOSURE_ABSOLUTE;
    ret = xioctl(handle->fd, VIDIOC_QUERYCTRL, &setting);
    printf("name: %s min: %d max: %d stp: %d def: %d\n", setting.name, setting.minimum, setting.maximum, setting.step, setting.default_value);

    setting.id = V4L2_CID_EXPOSURE;
    ret = xioctl(handle->fd, VIDIOC_QUERYCTRL, &setting);
    printf("name: %s min: %d max: %d stp: %d def: %d\n", setting.name, setting.minimum, setting.maximum, setting.step, setting.default_value);


    /* Buggy driver paranoia. */
    min = fmt.fmt.pix.width * 2;
    if (fmt.fmt.pix.bytesperline < min)
        fmt.fmt.pix.bytesperline = min;
    min = fmt.fmt.pix.bytesperline * fmt.fmt.pix.height;
    if (fmt.fmt.pix.sizeimage < min)
        fmt.fmt.pix.sizeimage = min;
    return init_mmap(handle);
}

static void close_device(capture_handle_t *handle)
{
    if (handle->fd >= 0) {
        close(handle->fd);
    }
    handle->fd = -1;
}
 
static int open_device(capture_handle_t *handle)
{
    struct stat st;

    if (-1 == stat(handle->dev_name, &st)) {
        printf("No video device\n");
        return -1;
    }

    if (!S_ISCHR(st.st_mode)) {
        fprintf(stderr, "%s is no device\n", handle->dev_name);
        return -1;
    }

    handle->fd = open(handle->dev_name, O_RDWR | O_NONBLOCK, 0);

    if (-1 == handle->fd) {
        fprintf(stderr, "Cannot open '%s': %d, %s\n", handle->dev_name, errno, strerror(errno));
        return -1;
    }
    return 0;
}

int type = 3;
int value = 2;
//static void* test_expose(void *arg) {
//    int fd = (long)arg;
//    while(1) {
//        sleep(2);
//        int ret;
//        struct v4l2_control ctrl;
//        memset(&ctrl, 0, sizeof(struct v4l2_control));
//        ctrl.id = V4L2_CID_EXPOSURE_AUTO;
//        ctrl.value = 3; //1 manual or 3 auto
//        ret = xioctl(fd, VIDIOC_S_CTRL, &ctrl);
//        if(ret < 0) {
//            perror("xioctl1");static void* test_expose(void *arg) {
//int fd = (long)arg;
//while(1) {
//    sleep(2);
//    int ret;
//    struct v4l2_control ctrl;
//    memset(&ctrl, 0, sizeof(struct v4l2_control));
//    ctrl.id = V4L2_CID_EXPOSURE_AUTO;
//    ctrl.value = 3; //1 manual or 3 auto
//    ret = xioctl(fd, VIDIOC_S_CTRL, &ctrl);
//    if(ret < 0) {
//        perror("xioctl1");
//        break;
//    }
//    memset(&ctrl, 0, sizeof(struct v4l2_control));
//    ctrl.id = V4L2_CID_EXPOSURE_ABSOLUTE;
//    ctrl.value = value; // 2-5000 def 30
//    value += 100;
//    ret = xioctl(fd, VIDIOC_S_CTRL, &ctrl);
//    if(ret < 0) {
//        perror("xioctl2");
//        break;
//    }
//    printf("exposure vaule: %d\n", ctrl.value);
//    sleep(2);
//}

//return NULL;
//}
//            break;
//        }
//        memset(&ctrl, 0, sizeof(struct v4l2_control));
//        ctrl.id = V4L2_CID_EXPOSURE_ABSOLUTE;
//        ctrl.value = value; // 2-5000 def 30
//        value += 100;
//        ret = xioctl(fd, VIDIOC_S_CTRL, &ctrl);
//        if(ret < 0) {
//            perror("xioctl2");
//            break;
//        }
//        printf("exposure vaule: %d\n", ctrl.value);
//        sleep(2);
//    }

//    return NULL;
//}

static void start_exposure_test(int fd) {
    pthread_t t1;
  // pthread_create(&t1, NULL, test_expose, (void *)(long)fd);
}

void* new_capture(int idx, void *callback)
{
    int i;
    char buf[32];
    struct stat st;

    if(idx < 0 || idx > CAPUTRE_MAX_IDX) return NULL;
    pthread_mutex_lock(&cap_mutex);
    for(i = 0; i <= CAPUTRE_MAX_IDX; i++) {
        sprintf(buf, CAPUTRE_DEV_FMT, i);
        if(stat(buf, &st) == 0) {
            idx--;
        }
        if(idx < 0) {
            break;
        }
    }
    capture_handle_t *handle = (capture_handle_t *)malloc(sizeof(capture_handle_t));
    memset(handle, 0, sizeof(capture_handle_t));
    if(handle == NULL) {
        goto end;
    }
    strcpy(handle->dev_name, buf);
    if(open_device(handle) < 0) {
        free(handle);
        handle = NULL;
        goto end;
    }
    if(init_device(handle) < 0) {
        close_device(handle);
        free(handle);
        handle = NULL;
        goto end;
    }
    handle->callback = (void *)callback;
    if(start_capturing(handle) < 0) {
        close_device(handle);
        free(handle);
        handle = NULL;
    }
end:
    pthread_mutex_unlock(&cap_mutex);
    if(handle != NULL) {
        start_exposure_test(handle->fd);
    }
    return handle;
}


void* new_capture_default(void *callback)
{
    return new_capture(dev_idx, callback);
}

void destroy_capture(capture_handle_t **handle)
{
    pthread_mutex_lock(&cap_mutex);
    if(handle != NULL && *handle != NULL) {
        capture_handle_t *p = *handle;
        p->stop_flag = 1;
        stop_capturing(p);
        uninit_device(p);
        close_device(p);
        free(*handle);
        *handle = NULL;
    }
    pthread_mutex_unlock(&cap_mutex);
}

int main(int argc, char const *argv[])
{
    if(argc > 1) {
        if(strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "-H") == 0) {
            printf("Usage: %s idx\n", argv[0]);
        } else {
            dev_idx = atoi(argv[1]);
        }
    }
    capture_handle_t *handle = (capture_handle_t *)new_capture(dev_idx, (void*)queue_push);
    ui_start();
    
    return 0;
}
