#include <queue>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"
#include "capture.h"

typedef struct {
    void *data;
    int len;
} Elem;

std::queue<Elem> q;
#define MAX_QUEUE_SIZE 8
#define MAX_EMPTY_COUNT 50
int empty_count = 0;

void queue_push(void *data, int len)
{
    if(len <= 0 || q.size() > MAX_QUEUE_SIZE) return;
    unsigned char *p = (unsigned char *)malloc(len+HUFFMAN_DATA_LEN);
    if(p == NULL) {
        return;
    }
    memcpy_picture(p, data, len);
    Elem e;
    e.data = p;
    e.len = len;
    q.push(e);
}

void queue_pop(void **data, int *len)
{
    *len = 0;
    *data = 0;
    if(!q.empty()) {
        empty_count = 0;
        Elem e = q.front();
        q.pop();
        *data = e.data;
        *len = e.len;
    } else {
        empty_count++;
        if(empty_count > MAX_EMPTY_COUNT) {
            empty_count = 0;
            //try reopen dev
            new_capture_default((void *)queue_push);
        }
    }
}

void queue_elem_free(void **data)
{
    if(data != NULL && *data != NULL) {
        free(*data);
        *data = NULL;
    }
}
