#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>
#include <memory.h>

typedef struct Queue
{
    void *buffer;     // data buffer
    void *buffer_end; // end of data buffer
    size_t capacity;  // maximum number of items in the buffer
    size_t count;     // number of items in the buffer
    size_t sz;        // size of each item in the buffer
    void *head;       // pointer to head
    void *tail;       // pointer to tail
} Queue;

void queue_init(Queue *cb, size_t capacity, size_t sz)
{
    cb->buffer = malloc(capacity * sz);
    if(cb->buffer == NULL)
        // handle error
    cb->buffer_end = (char *)cb->buffer + capacity * sz;
    cb->capacity = capacity;
    cb->count = 0;
    cb->sz = sz;
    cb->head = cb->buffer;
    cb->tail = cb->buffer;
}

void queue_free(Queue *cb)
{
    free(cb->buffer);
    // clear out other fields too, just to be safe
}

int queue_push_back(Queue *cb, const void *item)
{
    if(cb->count == cb->capacity){
        // overwrite
    }
    memcpy(cb->head, item, cb->sz);
    cb->head = (char*)cb->head + cb->sz;
    if(cb->head == cb->buffer_end)
        cb->head = cb->buffer;
    cb->count++;
    return 1;
}

int queue_pop_front(Queue *cb, void *item)
{
    if(cb->count == 0){
        return 0;
    }
    memcpy(item, cb->tail, cb->sz);
    cb->tail = (char*)cb->tail + cb->sz;
    if(cb->tail == cb->buffer_end)
        cb->tail = cb->buffer;
    cb->count--;
    return 1;
}

#endif