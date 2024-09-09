#ifndef ARENA_H
#define ARENA_H

#include <assert.h>
#include <stdlib.h>

struct arena *arena_init(size_t capacity);
void arena_discard(struct arena *a);

void *arena_top(struct arena *a);
void *arena_push(struct arena *a, size_t size);
void arena_pop(struct arena *a, size_t size);
size_t arena_used(struct arena *a);

void arena_append(struct arena *a, const char *s, int size);

#endif
