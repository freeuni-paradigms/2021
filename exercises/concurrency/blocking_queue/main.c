#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "vector.h"

#define QUEUESIZE 50

typedef struct
{
    vector vec;
    sem_t *read;
    sem_t *write;
    size_t elemSize;
    sem_t *lock;
} Queue;

void init_queue(Queue *q, int elemSize, VectorFreeFunction freefn)
{
    VectorNew(&q->vec, elemSize, freefn, 1);
    q->elemSize = elemSize;
    q->read = malloc(sizeof(sem_t));
    q->write = malloc(sizeof(sem_t));
    q->lock = malloc(sizeof(sem_t));

    sem_init(q->read, 0, 0);
    sem_init(q->write, 0, QUEUESIZE);
    sem_init(q->lock, 0, 1);
}

void enqueue(Queue *q, void *elem)
{
    sem_wait(q->write);

    sem_wait(q->lock);
    VectorAppend(&q->vec, elem);
    sem_post(q->lock);

    sem_post(q->read);
}

void dequeue(Queue *q, void **ptr)
{
    sem_wait(q->read);

    sem_wait(q->lock);
    void *elem = VectorNth(&q->vec, 0);
    void *newElem = malloc(q->elemSize);
    memcpy(newElem, elem, q->elemSize);
    *ptr = newElem;
    VectorDelete(&q->vec, 0);
    sem_post(q->lock);

    sem_post(q->write);
}

void destroy_queue(Queue *q)
{
    VectorDispose(&q->vec);
    sem_destroy(q->lock);
    sem_destroy(q->read);
    sem_destroy(q->write);

    free(q->lock);
    free(q->read);
    free(q->write);
    free(q);
}