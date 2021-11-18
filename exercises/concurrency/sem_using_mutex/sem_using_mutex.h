#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 

typedef struct {

} semT;

void semInit(semT * s, int value);

void semPost(semT * s);

void semWait(semT * s);