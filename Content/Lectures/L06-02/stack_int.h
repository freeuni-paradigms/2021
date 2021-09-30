typedef struct {
  int* base;
  int log_len;
  int alloc_len;
} Stack;

void StackInit(Stack* s);
void StackDestroy(Stack* s);
void StackPush(Stack* s, int value);
int StackPop(Stack* s);
