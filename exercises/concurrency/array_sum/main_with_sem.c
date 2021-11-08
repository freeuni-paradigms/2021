#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

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
}dataT;


void * calculateSum(void* datat){
    dataT* data = datat;
    int numSlice = ARRAY_LEN / NUM_THREADS;
    for (int i = 0; i < numSlice; i++){
        pthread_mutex_lock(data->lock);
        *data->sum += data->arr[numSlice * data->threadInd + i];
        pthread_mutex_unlock(data->lock);
    }
}

int main(){
    srand(time(NULL));

    int* arr = malloc(sizeof(int) * ARRAY_LEN);
    generateArray(arr);

    int * sum = malloc(sizeof(int));
    *sum = 0;
    pthread_mutex_t * lock = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(lock, NULL);

    pthread_t threads[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++){
        dataT* data = malloc(sizeof(dataT));
        data->arr = arr;
        data->threadInd = i;
        data->lock = lock;
        data->sum = sum;
        pthread_create(&threads[i], NULL, calculateSum, data);
    }

    for (int i = 0; i < NUM_THREADS; i++){
        pthread_join(threads[i], NULL);
    }

    printf("Calculated sum is %d\n", *sum);
}