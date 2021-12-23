#include "str_array2d.h"

#include <stdlib.h>
#include <string.h>

void FreeStr(void * elem) {
  free(*(char **)elem);
}

void StrArray2DInit(StrArray2D* arr, int n, int m) {
  Array2DInit(arr, n, m, sizeof(char*), FreeStr);
}

void StrArray2DDestroy(StrArray2D* arr) {
  Array2DDestroy(arr);
}

void StrArray2DSet(StrArray2D* arr, int i, int j, char* str) {
  Array2DSet(arr, i, j, &str);
}

const char* StrArray2DGet(StrArray2D* arr, int i, int j) {
  return *(char **)Array2DGet(arr, i, j);
}

typedef struct {
  StrArray2D* arr;
  const char* str;
  bool removed;
} RemoveData;

void IterMapFunc(void* aux, const void* elem, int i, int j) {
  RemoveData* data = aux;

  if (data->removed) {
    return;
  }

  if (strcmp(data->str, *(char**)elem) == 0) {
    Array2DRemove(data->arr, i, j);
    data->removed = true;
  }
}

bool StrArray2DRemove(StrArray2D* arr, const char* str) {
  // IMPLEMENT
  // მხოლოდ შეგიძლიათ აღწეროთ ლოკალური ცვლადები,
  // გამოიძახოთ Array2DIterate ფუნქცია და დააბრუნოთ მნიშვნელობა.
  RemoveData data;
  data.arr = arr;
  data.str = str;
  data.removed = false;
  Array2DIterate(arr, 0, 0, Array2DN(arr) - 1, Array2DM(arr) - 1, IterMapFunc, &data);
  return data.removed;
}
