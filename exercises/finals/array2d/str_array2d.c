#include "str_array2d.h"

#include <stdlib.h>
#include <string.h>

void StrArray2DInit(StrArray2D* arr, int n, int m) {
  // IMPLEMENT
}

void StrArray2DDestroy(StrArray2D* arr) {
  Array2DDestroy(arr);
}

void StrArray2DSet(StrArray2D* arr, int i, int j, char* str) {
  // IMPLEMENT
}

const char* StrArray2DGet(StrArray2D* arr, int i, int j) {
  // IMPLEMENT
  return NULL;
}

bool StrArray2DRemove(StrArray2D* arr, const char* str) {
  // IMPLEMENT
  // მხოლოდ შეგიძლიათ აღწეროთ ლოკალური ცვლადები,
  // გამოიძახოთ Array2DIterate ფუნქცია და დააბრუნოთ მნიშვნელობა.
  return false;
}
