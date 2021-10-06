#include "sortedset.h"

/*
* Function: SetNew
* Usage: SetNew(&stringSet, sizeof(char *), StringPtrCompare);
*
SetNew(&constellations, sizeof(pointT), DistanceCompare);
* ----------------
* SetNew allocates the requisite space needed to manage what
* will initially be an empty sorted set. More specifically, the
* routine allocates space to hold up to 'kInitialCapacity' (currently 4)
* client elements.
*/
static const int kInitialCapacity = 4;
void SetNew(sortedset *set, int elemSize, int (*cmpfn)(const void *, const void *), void (*freefn)(const void *))
{
    assert(elemSize > 0);
    assert(cmpfn != NULL);
    set->elemSize = elemSize;
    set->cmpfn = cmpfn;
    set->freefn = freefn;
    set->allocLen = kInitialCapacity;
    set->logLen = 0;
    set->nodeSize = set->elemSize + 2 * sizeof(int);

    set->base = malloc(sizeof(int) + set->allocLen * set->nodeSize);
    *(set->base) = -1;
}

/*
* Function: SetSearch
* Usage: if (SetSearch(&staffSet, &lecturer) == NULL)
*
printf("musta been fired");
* -------------------
* SetSearch searches for the specified client element according
* the whatever comparison function was provided at the time the
* set was created. A pointer to the matching element is returned
* for successful searches, and NULL is returned to denote failure.
*/
void *SetSearch(sortedset *set, const void *elemPtr)
{
    int *indexPtr = FindNode(set, elemPtr);

    int index = *indexPtr;

    if (index == -1)
        return NULL;

    int offset = sizeof(int) + set->nodeSize * index;
    void *elem = (char *)(set->base) + offset;

    return elem;
}
/*
* Function: SetAdd
* Usage: if (!SetAdd(&friendsSet, &name)) free(name);
* ----------------
* Adds the specified element to the set if not already present.
* present, the client element is not copied into the set. true
* is returned if and only if the element at address elemPtr
* was copied into the set.
*/
bool SetAdd(sortedset *set, const void *elemPtr)
{
    int *indexPtr = FindNode(set, elemPtr);

    int index = *indexPtr;

    if (index != -1)
        return false;

    if (set->allocLen == set->logLen)
    {
        set->allocLen *= 2;
        set->base = realloc(set->base, sizeof(int) + set->allocLen * set->nodeSize);
    }

    void *dest = (char *)(set->base) + sizeof(int) + set->logLen * set->nodeSize;
    memcpy(dest, elemPtr, set->elemSize);
    int *arr = (int *)((char *)dest + set->elemSize);
    arr[0] = -1; // *arr = -1;
    arr[1] = -1; // *((char *)arr + sizeof(int)) = -1; // *(arr + 1) = 0;

    *indexPtr = set->logLen;
    set->logLen++;

    return true;
}

/**
* Function: FindNode
* Usage: ip = FindNode(set, elem);
*
if (*ip == -1) printf("ip points where this element belongs!");
* ------------------
* FindNode descends through the underlying binary search tree of the
* specified set and returns the address of the offset into raw storage
* where the specified element resides. If the specified element isn't
* in the set, FindNode returns the address of the –1 that would be updated
* to contain the index of the element being sought if it were the
* element to be inserted——that is, the address of the –1 that ended
* the search.
*/
static int *FindNode(sortedset *set, const void *elem)
{
    int *indexPtr = set->base;
    while (*indexPtr != -1)
    {
        int index = *indexPtr;
        int offset = sizeof(int) + set->nodeSize * index;
        void *current = (char *)(set->base) + offset;

        int result = set->cmpfn(current, elem);

        if (result == 0)
            break;

        if (result < 0)
        {
            // Right
            indexPtr = (int *)((char *)current + set->elemSize + sizeof(int));
        }
        else
        {
            // Left
            indexPtr = (int *)((char *)current + set->elemSize);
        }
    }

    return indexPtr;
}

void destruct(sortedset *set)
{
    if (set->freefn != NULL)
    {
        void *current = set->base + 1;
        for (int i = 0; i < set->logLen; i++)
        {
            void *elem = (char *)(set->base) + sizeof(int) + set->nodeSize * i;
            set->freefn(elem);
        }
    }
    free(set->base);
}