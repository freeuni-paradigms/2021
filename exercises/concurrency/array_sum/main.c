#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define ARRAY_LEN 100
#define NUM_THREADS 10
#define MAX_NUM 10000

void generateArray(int *arr)
{
    int sum = 0;
    for (int i = 0; i < ARRAY_LEN; i++)
    {
        arr[i] = rand() % MAX_NUM;
        sum += arr[i];
    }
    printf("Sum of array is %d\n", sum);
}

int main()
{
    srand(time(NULL));
}