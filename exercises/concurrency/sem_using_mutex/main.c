#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include "sem_using_mutex.h"
#define MAX_NUM 100

void RandomSleep() {
	int k = rand();
	if (k % 3 == 0) {
		usleep(100);
	}
}
typedef struct {
	int counter;
	semT * evenLock;
	semT * oddLock;
} dataT;

void * EvenPrinter(void * data) {
    dataT* dataT = data;
    for (int i = 2; i <= MAX_NUM; i += 2) {
        semWait(dataT->evenLock);
        printf("Even printer: %d\n", i);
        semPost(dataT->oddLock);
    }
}

void * OddPrinter(void * data) {
    dataT* dataT = data;
    for (int i = 1; i <= MAX_NUM; i += 2) {
        semWait(dataT->oddLock);
        printf("Odd printer: %d\n", i);
        semPost(dataT->evenLock);
    }
}

// gcc main.c sem_using_mutex.c -lpthread
int main() {
	pthread_t * tEven = malloc(sizeof(pthread_t));
	pthread_t * tOdd = malloc(sizeof(pthread_t));

	dataT * data = malloc(sizeof(dataT));
	data->counter = 0;
	data->evenLock = malloc(sizeof(semT));
	data->oddLock = malloc(sizeof(semT));
	semInit(data->evenLock, 0);
	semInit(data->oddLock, 1);

	pthread_create(tEven, NULL, EvenPrinter, data);
	pthread_create(tOdd, NULL, OddPrinter, data);


 	pthread_join(*tEven, NULL);
   	pthread_join(*tOdd, NULL);
	
	free(tEven);
	free(tOdd);
	free(data->evenLock);
	free(data->oddLock);
	free(data);

	pthread_exit(NULL);
}