#include "sol_sorted_multi_set.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define NOT_FOUND -1

typedef struct {
  int count;
  void * elem;
  FreeFn free_fn;
} Item;

static void ItemFree(void * elem) {
  Item * item = elem;
  if (item->free_fn != NULL) {
    item->free_fn(item->elem);
  }
  free(item->elem);
}

void SortedMultiSetInit(SortedMultiSet* s, int elem_size, CmpFn cmp_fn, FreeFn free_fn) {
  s->elem_size = elem_size;
  s->cmp_fn = cmp_fn;
  s->free_fn = free_fn;
  VectorInit(&s->v, sizeof(Item), ItemFree);
}

void SortedMultiSetDestroy(SortedMultiSet* s) {
  VectorDestroy(&s->v);
}

typedef struct {
  void * elem;
  int insert_pos;
  CmpFn cmp_fn;
  bool contains;
} InsertAux;

static void InsetMapFunc(int index, void* elem, void* aux) {
  Item* item = elem;
  InsertAux* insertAux = aux;

  if (insertAux->contains || insertAux->insert_pos != NOT_FOUND) {
    return;
  }

  int cmpValue = insertAux->cmp_fn(insertAux->elem, item->elem);
  if (cmpValue == 0) {
    insertAux->contains = true;
    insertAux->insert_pos = index;
    item->count++;
  } else if (cmpValue < 0) {
    insertAux->insert_pos = index;
  }
}

int SortedMultiSetInsert(SortedMultiSet* s, void* elem) {
  InsertAux aux;
  aux.cmp_fn = s->cmp_fn;
  aux.contains = false;
  aux.elem = elem;
  aux.insert_pos = NOT_FOUND;
  VectorMap(&s->v, InsetMapFunc, &aux);

  if (aux.contains) {
    if (s->free_fn != NULL) {
      s->free_fn(elem);
    }
    return aux.insert_pos;
  }

  if (aux.insert_pos == NOT_FOUND) {
    aux.insert_pos = VectorSize(&s->v);
  }

  Item newItem;
  newItem.count = 1;
  // newItem.elem = elem; ეს არასწორია, რადგან შეიძლება სტეკში გამოყოფილ ელემენტის მისამართი მოგვცეს, აუცილებლად უნდა გადავიკოპიროთ.
  newItem.elem = malloc(s->elem_size);
  memcpy(newItem.elem, elem, s->elem_size);
  newItem.free_fn = s->free_fn;

  VectorInsert(&s->v, aux.insert_pos, &newItem);
  return aux.insert_pos;
}

typedef struct {
  int index;
  void* elem;
} GetAux;

static void GetMapFunc(int index, void* elem, void* aux) {
  Item* item = elem;
  GetAux* getAux = aux;

  if (getAux->index == index) {
    getAux->elem = item->elem;
  }
}

void* SortedMultiSetGet(SortedMultiSet* s, int index) {
  GetAux aux;
  aux.index = index;
  aux.elem = NULL;
  VectorMap(&s->v, GetMapFunc, &aux);
  return aux.elem;
}

typedef struct {
  int count;
  void * elem;
  CmpFn cmp_fn;
} GetCountAux;

static void GetCountMapFunc(int index, void* elem, void* aux) {
  Item * item = elem;
  GetCountAux * getCountAux = aux;

  if (getCountAux->cmp_fn(item->elem, getCountAux->elem) == 0) {
    getCountAux->count = item->count;
  }
}

int SortedMultiSetGetCount(SortedMultiSet* s, void* elem) {
  GetCountAux aux;
  aux.cmp_fn = s->cmp_fn;
  aux.count = 0;
  aux.elem = elem;
  VectorMap(&s->v, GetCountMapFunc, &aux);
  return aux.count;
}
