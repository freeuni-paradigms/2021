#include "sem_using_mutex.h"


void semInit(semT * s, int value) {
    s->counter = value;
    s->mutex = malloc(sizeof(pthread_mutex_t));
    s->cond = malloc(sizeof(pthread_cond_t));
    pthread_mutex_init(s->mutex, NULL);
    pthread_cond_init(s->cond, NULL);
}

void semPost(semT * s) {
    pthread_mutex_lock(s->mutex);
    s->counter++;
    pthread_cond_signal(s->cond);
    pthread_mutex_unlock(s->mutex);
}

void semWait(semT * s) {
    pthread_mutex_lock(s->mutex);
    while (s->counter == 0) {
        pthread_cond_wait(s->cond, s->mutex);
    }
    s->counter--;
    pthread_mutex_unlock(s->mutex);
}