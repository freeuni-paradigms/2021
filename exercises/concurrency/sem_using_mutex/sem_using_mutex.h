#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct
{
    int value;
    pthread_mutex_t *lock;
    pthread_cond_t *cond;
} semT;

void semInit(semT *s, int value);

void semPost(semT *s);

void semWait(semT *s);