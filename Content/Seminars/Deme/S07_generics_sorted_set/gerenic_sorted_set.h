#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int *root;
    int logLen;
    int allocLen;
    int elemSize;
    int (*cmpfn)(const void *, const void *);
} sortedset;

void SetNew(sortedset *set, int elemSize, int (*cmpfn)(const void *, const void *));
bool SetAdd(sortedset *set, const void *elemPtr);
void *SetSearch(sortedset *set, const void *elemPtr);