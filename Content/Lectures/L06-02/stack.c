#include "stack.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

void StackInit(Stack* s, int elem_size) {
  s->elem_size = elem_size;
  s->log_len = 0;
  s->alloc_len = 4;
  s->base = malloc(s->alloc_len * elem_size);
  assert(s->base != NULL);
}

void StackDestroy(Stack* s) {
  free(s->base);
}

void StackPush(Stack* s, void* value) {
  if (s->log_len == s->alloc_len) { // Grow
    s->alloc_len *= 2;
    s->base = realloc(s->base, s->alloc_len * s->elem_size);
    assert(s->base != NULL);
  }
  memcpy((char*)s->base + s->log_len * s->elem_size, value, s->elem_size);
  s->log_len++;
}

void StackPop(Stack* s, void* out) {
  assert(s->log_len > 0);
  assert(out != NULL);
  s->log_len--;
  memcpy(out, (char*)s->base + s->log_len * s->elem_size, s->elem_size);
}
