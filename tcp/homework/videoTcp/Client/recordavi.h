/*************************************************
  author ZhouXiang
  此类的功能：从外部接受连续的图片数据以视频形式保存
  此类是在另一个线程中执行，确保GUI线程能够得到灵活的响应
  ***********************************************/
#ifndef RECORDAVI_H
#define RECORDAVI_H

#include <QObject>
#include <QImage>
#include <QFile>
#include <QTime>

#include <opencv/cv.h>
#include <opencv/highgui.h>

class RecordAVI : public QObject
{
    Q_OBJECT
public:
    explicit RecordAVI(QObject *parent = 0);
    ~RecordAVI();
signals:
    void _error();
public slots:
    /******************
      函数名：getImage
      参数：QImage类型
      简述：一个public slots供外部调用，接受一幅图片，供类中进行操作
      *******************/
    void getImage(const QImage&);//接受图片
private:
    QFile *imageFile;
    CvVideoWriter *writer;//创建视频文件写入器
    IplImage *frame;//
};

#endif // RECORDAVI_H
