#ifndef PARADIGMS_PROBLEMS_MAPSET_SORTED_MULTI_SET_H_
#define PARADIGMS_PROBLEMS_MAPSET_SORTED_MULTI_SET_H_

#include "vector.h"

typedef int(*CmpFn)(void* a, void* b);

typedef struct {
  Vector v;
  int elem_size;
  CmpFn cmp_fn;
  FreeFn free_fn;
} SortedMultiSet;

void SortedMultiSetInit(SortedMultiSet* s, int elem_size, CmpFn cmp_fn, FreeFn free_fn);
void SortedMultiSetDestroy(SortedMultiSet* s);
int SortedMultiSetInsert(SortedMultiSet* s, void* elem);
void* SortedMultiSetGet(SortedMultiSet* s, int index);
int SortedMultiSetGetCount(SortedMultiSet* s, void* elem);

#endif  // PARADIGMS_PROBLEMS_MAPSET_SORTED_MULTI_SET_H_
