#include "thread.h"

Thread::Thread() { stop = 0;}
Thread::~Thread() {}

void Thread::run()
{
    while(!stop) {
        emit ImageSignal();
        usleep(Thread_SLEEP_MS * 1000);
    }
}

void Thread::SetStop(void) { stop = 1; }
