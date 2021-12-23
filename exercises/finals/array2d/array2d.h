#ifndef PARADIGMS_ARRAY2D_H_
#define PARADIGMS_ARRAY2D_H_

#include <stdbool.h>

typedef void(*FreeFn)(void* elem);
typedef void(*IterFn)(void* aux, const void* elem, int i, int j);

typedef struct {
  // აქ დაამატეთ საჭირო ცვლადები
  void* base;
  bool* is_set;
  int n;
  int m;
  int elem_size;
  FreeFn free_fn;
} Array2D;

// უკეთებს ინიციალიზაციას მასივს.
void Array2DInit(Array2D* arr, int n, int m, int elem_size, FreeFn free_fn);
// ათავისუფლებს მასივის მიერ გამოყენებულ მეხსიერებას.
void Array2DDestroy(Array2D* arr);
// აბრუნებს მასივში ხაზების რაოდენობას.
int Array2DN(Array2D* arr);
// აბრუნებს მასივში სვეტების რაოდენობას.
int Array2DM(Array2D* arr);
// მასივში (i, j) პოზიციაზე წერს value-ს რომელზეც იღებს მფლობელობას.
void Array2DSet(Array2D* arr, int i, int j, void* value);
// ამრუნებს მასივის (i, j) ელემენტზე მისამართს.
// მფლობელობას არ გადასცემს გამომძახებელს.
const void* Array2DGet(Array2D* arr, int i, int j);
void Array2DRemove(Array2D* arr, int i, int j);
// მასივის (x, y) .. (w, z) შუალედში ყველა ელემენტისთვის იძახებს iter_fn ფუნქციას.
void Array2DIterate(Array2D* arr, int x, int y, int w, int z, IterFn iter_fn, void* aux);
// ზრდის მასივის ზომას.
void Array2DGrow(Array2D* arr, int n, int m);

#endif // PARADIGMS_ARRAY2D_H_
