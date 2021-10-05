#ifndef __STACK_H__
#define __STACK_H__

typedef void(*FreeFn)(void*);
ReturnType(*FunctionTypeName)(Arg1Type, Arg2Type, ...)
void(void*) FreeFn

typedef definition name;

typedef struct {
  void* base;
  int elem_size;
  int log_len;
  int alloc_len;
  FreeFn free_fn;
} Stack;

void StackInit(Stack* s, int elem_size,
	       FreeFn free_fn);
void StackDestroy(Stack* s);
void StackPush(Stack* s, void* value);
void StackPop(Stack* s, void* out);

#endif // __STACK_H__
