#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define NUM_RACERS 10
#define DISTANCE 100

void RandomSleep()
{
    int k = rand();
    if (k % 3 == 0)
    {
        usleep(100);
    }
}

typedef struct
{
    int id;
    int *place;
    sem_t *lock;
} data_T;

void *race(void *datat)
{
    data_T *data = (data_T *)datat;
    for (int i = 0; i < DISTANCE; i++)
        RandomSleep();

    int id = data->id;
    sem_wait(data->lock);
    int place = *(data->place);
    *(data->place) = place + 1;
    sem_post(data->lock);
    printf("Racer %d: Place %d\n", id, place);
}

int main()
{
    srand(time(NULL));

    int *place = malloc(sizeof(int));
    *place = 1;

    sem_t *lock = malloc(sizeof(sem_t));
    sem_init(lock, 0, 1);

    pthread_t racers[NUM_RACERS];
    for (int i = 0; i < NUM_RACERS; i++)
    {
        data_T *data = malloc(sizeof(data_T));
        data->id = i + 1;
        data->place = place;
        data->lock = lock;
        pthread_create(&racers[i], NULL, race, data);
    }

    pthread_exit(NULL);
}