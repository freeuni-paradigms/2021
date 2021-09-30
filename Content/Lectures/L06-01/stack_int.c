#include "stack_int.h"

#include <assert.h>
#include <stdlib.h>

void StackInit(Stack* s) {
  s->log_len = 0;
  s->alloc_len = 4;
  s->base = malloc(s->alloc_len * sizeof(int));
  assert(s->base != NULL);
}

void StackDestroy(Stack* s) {
  free(s->base);
}

void StackPush(Stack* s, int value) {
  if (s->log_len == s->alloc_len) {
    s->alloc_len *= 2;
    s->base = realloc(s->base, s->alloc_len * sizeof(int));
    assert(s->base != NULL);
  }
  s->base[s->log_len] = value;
  s->log_len++;
}

int StackPop(Stack* s) {
  assert(s->log_len > 0);
  s->log_len--;
  return s->base[s->log_len];
}
