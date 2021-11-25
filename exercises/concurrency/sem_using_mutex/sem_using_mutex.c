#include "sem_using_mutex.h"

void semInit(semT *s, int value)
{
    s->value = value;
    s->lock = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(s->lock, NULL);
    s->cond = malloc(sizeof(pthread_cond_t));
    pthread_cond_init(s->cond, NULL);
}

void semPost(semT *s)
{
    pthread_mutex_lock(s->lock);
    s->value++;
    pthread_mutex_unlock(s->lock);
    pthread_cond_signal(s->cond);
}

void semWait(semT *s)
{
    pthread_mutex_lock(s->lock);
    while (s->value == 0)
    {
        pthread_cond_wait(s->cond, s->lock);
    }
    s->value--;
    pthread_mutex_unlock(s->lock);
}