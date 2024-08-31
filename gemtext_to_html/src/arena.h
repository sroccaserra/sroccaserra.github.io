#ifndef ARENA_H
#define ARENA_H

#include <assert.h>
#include <stdlib.h>

struct arena {
    size_t capacity;
    size_t used;
    char *mem;
};

struct arena arena_init(size_t capacity);
void arena_discard(struct arena *a);

#define arena_pointer(a) ((void *)((a)->mem + (a)->used))
void *arena_push(struct arena *a, size_t size);
void arena_pop(struct arena *a, size_t size);
size_t arena_used(struct arena *a);

#endif
