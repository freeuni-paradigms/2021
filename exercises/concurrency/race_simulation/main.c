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

int main()
{
    srand(time(NULL));
}