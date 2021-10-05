#include <gerenic_sorted_set.h>

#define NodeSize(elemSize) ((elemSize) + 2 * sizeof(int))

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
void SetNew(sortedset *set, int elemSize, int (*cmpfn)(const void *, const void *)) {
    assert(elemSize > 0);
    assert(cmpfn != NULL);

    set->logLen = 0;
    set->allocLen = kInitialCapacity;
    set->cmpfn = cmpfn;
    set->elemSize = elemSize;
    set->root = malloc(sizeof(int) + set->allocLen * NodeSize(set->elemSize));
    assert(set->root != NULL);
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
void *SetSearch(sortedset *set, const void *elemPtr) {
    int *node = FindNode(set, elemPtr);
    if (*node == -1) return NULL;
    return (char *)(set->root + 1) + *node * NodeSize(set->elemSize);
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
bool SetAdd(sortedset *set, const void *elemPtr) {
    int *node = FindNode(set, elemPtr);
    if (*node != -1) {
        return false;
    }

    if (set->allocLen == set->logLen) {
        set->allocLen *= 2;
        set->root = realloc(set->root, sizeof(int) + set->allocLen * NodeSize(set->elemSize));
        assert(set->root != NULL);
    }

    *node = set->logLen;
    set->logLen++;

    void *dst = (char *)(set->root + 1) + *node * NodeSize(set->elemSize);
    memcpy(dst, elemPtr, set->elemSize);
    int *childs = (int*)((char*)dst + set->elemSize);
    childs[0] = -1;
    childs[1] = -1;
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
static int *FindNode(sortedset *set, const void *elem) {
   void *currElem;
   int *node = set->root;

   while (*node != -1) {
       currElem = (char *)(set->root + 1) + *node * NodeSize(set->elemSize);
       int cmp = set->cmpfn(elem, currElem);
       if (cmp == 0) {
           return node;
       }
       node = (int *)((char *)currElem + set->elemSize);
       if (cmp > 0) {
           node++;
       }
   }
   return node;
}