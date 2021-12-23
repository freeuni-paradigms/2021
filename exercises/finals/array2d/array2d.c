#include "array2d.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

void Array2DInit(Array2D* arr, int n, int m, int elem_size, FreeFn free_fn) {
  // IMPLEMENT
}

void Array2DDestroy(Array2D* arr) {
  // IMPLEMENT
}

int Array2DN(Array2D* arr) {
  // IMPLEMENT
  return 0;
}

int Array2DM(Array2D* arr) {
  //IMPLEMENT
  return 0;
}

void Array2DSet(Array2D* arr, int i, int j, void* value) {
  // IMPLEMENT
}

const void* Array2DGet(Array2D* arr, int i, int j) {
  // IMPLEMENT
  return NULL;
}

void Array2DRemove(Array2D* arr, int i, int j) {
  // IMPLEMENT
}

void Array2DIterate(Array2D* arr, int x, int y, int w, int z, IterFn iter_fn, void* aux) {
  // IMPLEMENT
}

void Array2DGrow(Array2D* arr, int n, int m) {
  // IMLPEMENT
}
