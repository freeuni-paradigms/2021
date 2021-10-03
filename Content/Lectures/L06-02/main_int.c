#include <stdio.h>

#include "stack_int.h"

int main(int argc, char** argv) {
  Stack s;
  StackInit(&s);
  StackPush(&s, 2);
  StackPush(&s, 5);
  printf("%d\n", StackPop(&s));
  StackPush(&s, 3);
  printf("%d\n", StackPop(&s));
  printf("%d\n", StackPop(&s));
  StackDestroy(&s);
  return 0;
}
