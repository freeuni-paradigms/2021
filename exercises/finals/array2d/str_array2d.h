#ifndef PARADIGMS_STR_ARRAY2D_H_
#define PARADIGMS_STR_ARRAY2D_H_

#include "array2d.h"

typedef Array2D StrArray2D;

// უკეთებს მასივს ინიციალიზაციას.
void StrArray2DInit(StrArray2D* arr, int n, int m);
// ათავისუფლებს მასივის მიერ გამოყენებულ მეხსიერებას.
void StrArray2DDestroy(StrArray2D* arr);
// მასივში (i, j) პოზიციაზე წერს მოცემულ სტრიქონს.
// იღებს მფლობელობას მოცემულ სტრიქონზე.
void StrArray2DSet(StrArray2D* arr, int i, int j, char* str);
// აბრუნებს მასივში (i, j) პოზიციაზე მყოფ სტრიქონს.
// დაბრუნებულ სტრიქონზე მფლობელობას არ გადასცემს გამომძახებელს.
const char* StrArray2DGet(StrArray2D* arr, int i, int j);
// მასივში პოულობს პირველ სტრიქონს რომელიც ტოლია მოცემულ str-ის და შლის მას მასივიდან.
// არ იღებს მფლობელობას გადმოცემულ სტრიქონზე.
bool StrArray2DRemove(StrArray2D* arr, const char* str);

#endif  // PARADIGMS_STR_ARRAY2D_H_
