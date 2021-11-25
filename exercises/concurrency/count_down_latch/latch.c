#include "latch.h"

void latchInit(latchT * s, int value) {
    s->counter = value;
    s->mutex = malloc(sizeof(pthread_mutex_t));
    s->cond = malloc(sizeof(pthread_cond_t));
    pthread_mutex_init(s->mutex, NULL);
    pthread_cond_init(s->cond, NULL);
}

void countdown(latchT * s) {
    pthread_mutex_lock(s->mutex);
    s->counter--;
    if (s->counter == 0) {
        pthread_cond_signal(s->cond);
    }
    pthread_mutex_unlock(s->mutex);
}

void await(latchT * s) {
    pthread_mutex_lock(s->mutex);
    while (s->counter > 0) {
        pthread_cond_wait(s->cond, s->mutex);
    }
    pthread_mutex_unlock(s->mutex);
}