#ifndef __STACK_H_
#define __STACK_H_

typedef struct {
  int* base;
  int log_len;
  int alloc_len;
} Stack;

void StackInit(Stack* s);
void StackDestroy(Stack* s);
void StackPush(Stack* s, int value);
int StackPop(Stack* s);

#endif // __STACK_H_
