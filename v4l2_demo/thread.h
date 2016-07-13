#ifndef THREAD_H_
#define THREAD_H_

#include <QtCore>

#define Thread_SLEEP_MS 33

class Thread : public QThread
{
    Q_OBJECT
private:
    int stop;
protected:
    void run();
public:
    void SetStop(void);
    Thread();
    ~Thread();
signals:
    void ImageSignal();
};

#endif
