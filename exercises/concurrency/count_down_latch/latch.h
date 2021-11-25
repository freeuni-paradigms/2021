#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 

typedef struct {
    int counter;
    pthread_mutex_t* mutex;
    pthread_cond_t* cond;
} latchT;

void latchInit(latchT * s, int value);

void countdown(latchT * s);

void await(latchT * s);