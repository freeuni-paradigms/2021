#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "latch.h"

#define ARRAY_LEN 100
#define NUM_THREADS 10
#define MAX_NUM 10000

void generateArray(int* arr){
    int sum = 0;
    for (int i = 0; i < ARRAY_LEN; i++){
        arr[i] = rand() % MAX_NUM;
        sum += arr[i];
    }
    printf("Sum of array is %d\n", sum);
}

typedef struct{
    int * arr;
    int threadInd;
	pthread_mutex_t * lock;
    int * sum;
    latchT* latch;
}dataT;


void * calculateSum(void* datat){
    dataT* data = datat;
    int numSlice = ARRAY_LEN / NUM_THREADS;
    for (int i = 0; i < numSlice; i++){
        pthread_mutex_lock(data->lock);
        *data->sum += data->arr[numSlice * data->threadInd + i];
        pthread_mutex_unlock(data->lock);
    }
    printf("Thread with Id: %d finished it's work\n", data->threadInd);
    countdown(data->latch);
}

int main(){
    srand(time(NULL));

    int* arr = malloc(sizeof(int) * ARRAY_LEN);
    generateArray(arr);

    int * sum = malloc(sizeof(int));
    *sum = 0;
    pthread_mutex_t * lock = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(lock, NULL);

    latchT* latch = malloc(sizeof(latchT));
    latchInit(latch, NUM_THREADS);

    pthread_t threads[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++){
        dataT* data = malloc(sizeof(dataT));
        data->arr = arr;
        data->threadInd = i;
        data->lock = lock;
        data->sum = sum;
        data->latch = latch;
        pthread_create(&threads[i], NULL, calculateSum, data);
    }

    await(latch);
    printf("Calculated sum is %d\n", *sum);
}