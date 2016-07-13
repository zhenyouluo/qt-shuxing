#ifndef QUEUE_H_ 
#define QUEUE_H_ 

void queue_push(void *data, int len);
void queue_pop(void **data, int *len);
void queue_elem_free(void **data);


#endif