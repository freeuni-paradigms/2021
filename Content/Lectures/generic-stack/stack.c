#include "stack.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

void StackInit(Stack* s, int elem_size,
	       FreeFn free_fn) {
  s->elem_size = elem_size;
  s->log_len = 0;
  s->alloc_len = 4;
  s->base = malloc(s->alloc_len * elem_size);
  assert(s->base != NULL);
  s->free_fn = free_fn;
}

void StackDestroy(Stack* s) {
  if (s->free_fn != NULL) {
    for (int i = 0; i < s->log_len; i++) {
      s->free_fn((char*)s->base + s->log_len * s->elem_size);
    }
  }
  free(s->base);
}

// Takes ownership of memory at value.
void StackPush(Stack* s, void* value) {
  if (s->log_len == s->alloc_len) {
    s->alloc_len *= 2;
    s->base = realloc(s->base, s->alloc_len * s->elem_size);
    assert(s->base != NULL);
  }
  memcpy((char*)s->base + s->log_len * s->elem_size, value, s->elem_size);
  s->log_len++;
}

// Transfers ownership back to the client.
void StackPop(Stack* s, void* out) {
  assert(s->log_len > 0);
  s->log_len--;
  memcpy(out, (char*)s->base + s->log_len * s->elem_size, s->elem_size);
}





