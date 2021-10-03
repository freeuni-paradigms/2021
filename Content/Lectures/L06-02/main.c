#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

int main(int argc, char** argv) {
  Stack s;
  StackInit(&s, sizeof(int));
  int x = 2;
  StackPush(&s, &x);
  int y;
  StackPop(&s, &y);
  printf("%d\n", y);
  x = 5;
  StackPush(&s, &x);
  printf("%d\n", y);
  int* z = malloc(sizeof(int));
  StackPop(&s, z);
  printf("%d\n", z);
  free(z);
  StackDestroy(&s);
  return 0;
}
