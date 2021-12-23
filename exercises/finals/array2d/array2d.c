#include "array2d.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define ELEM(arr, i, j) ((char*)(arr)->base + ((i) * (arr)->m + (j)) * (arr)->elem_size)
#define IS_SET(arr, i, j) ((char*)(arr)->is_set + ((i) * (arr)->m + (j)) * sizeof(bool))


void Array2DInit(Array2D* arr, int n, int m, int elem_size, FreeFn free_fn) {
  arr->base = malloc(n * m * elem_size);
  assert(arr->base != NULL);

  arr->is_set = malloc(n * m * sizeof(bool));
  assert(arr->is_set != NULL);

  memset(arr->is_set, 0, n * m * sizeof(bool));
  
  arr->n = n;
  arr->m = m;
  arr->elem_size = elem_size;
  arr->free_fn = free_fn;
}

void Array2DDestroy(Array2D* arr) {
  if (arr->free_fn != NULL) {
    for (int i = 0; i < arr->n; i++) {
      for (int j = 0; j < arr->m; j++) {
        if (*IS_SET(arr, i, j)) {
          arr->free_fn(ELEM(arr, i, j));
        }
      }
    }
  }
  free(arr->base);
  free(arr->is_set);
}

int Array2DN(Array2D* arr) {
  return arr->n;
}

int Array2DM(Array2D* arr) {
  return arr->m;
}

void Array2DSet(Array2D* arr, int i, int j, void* value) {
  if (*IS_SET(arr, i, j) && arr->free_fn != NULL) {
    arr->free_fn(ELEM(arr, i, j));
  }
  
  memcpy(ELEM(arr, i, j), value, arr->elem_size);
  *IS_SET(arr, i, j) = true;
}

const void* Array2DGet(Array2D* arr, int i, int j) {
  return ELEM(arr, i, j);
}

void Array2DRemove(Array2D* arr, int i, int j) {
  if (*IS_SET(arr, i, j)) {
    if (arr->free_fn != NULL) {
      arr->free_fn(ELEM(arr, i, j));
    }
    *IS_SET(arr, i, j) = false;
  }
}

void Array2DIterate(Array2D* arr, int x, int y, int w, int z, IterFn iter_fn, void* aux) {
  for (int i = x; i <= w; i++) {
    for (int j = y; j <= z; j++) {
      if (*IS_SET(arr, i, j)) {
        iter_fn(aux, ELEM(arr, i, j), i, j);
      }
    }
  }
}

void Array2DGrow(Array2D* arr, int n, int m) {
  void * new_base = malloc(n * m * arr->elem_size);
  assert(new_base != NULL);

  bool * new_is_set = malloc(n * m * sizeof(bool));
  assert(new_is_set != NULL);

  memset(new_is_set, 0, n * m * sizeof(bool));

  for (int i = 0; i < arr->n; i++) {
    memcpy(
      (char*)new_base + i * m * arr->elem_size,
      (char*)arr->base + i * arr->m * arr->elem_size,
      arr->m * arr->elem_size
    );

    memcpy(
      (char*)new_is_set + i * m * sizeof(bool),
      (char*)arr->is_set + i * arr->m * sizeof(bool),
      arr->m * sizeof(bool)
    );
  }

  free(arr->base);
  arr->base = new_base;
  free(arr->is_set);
  arr->is_set = new_is_set;
  arr->n = n;
  arr->m = m;
}
