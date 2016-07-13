#ifndef CAPTURE_H
#define CAPTURE_H

typedef int (*callback_func)(void*, int);
void* new_capture(int idx, void* callback);
void* new_capture_default(void *callback);

#endif
