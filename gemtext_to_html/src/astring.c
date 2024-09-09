#include <stdbool.h>
#include <string.h>

#include "arena.h"
#include "astring.h"

struct astring *astring_init(struct arena *a, const char *cstr) {
    struct astring *result = arena_push(a, sizeof(struct astring));
    result->size = strlen(cstr);
    result->items = cstr;
    return result;
}

struct astring *astring_init_ln(struct arena *a, const char *cstr, int size) {
    struct astring *result = arena_push(a, sizeof(struct astring));
    result->size = size;
    result->items = cstr;
    return result;
}

void astring_set_cstr(struct astring *self, char *cstr) {
    self->size = strlen(cstr);
    self->items = cstr;
}

void astring_set_cstr_ln(struct astring *self, char *cstr, int size) {
    self->size = size;
    self->items = cstr;
}

bool astring_is_same(struct astring *self, char *cstr) {
    return 0 == strncmp(self->items, cstr, self->size);
}

char *astring_to_cstr(struct arena *a, struct astring *self) {
    int size = self->size;
    char *result = arena_push(a, size + 1);
    strncpy(result, self->items, size);
    result[size] = '\0';
    return result;
}

int astring_sprint(struct astring *self, char *buffer) {
    int size = self->size;
    strncpy(buffer, self->items, size);
    return size;
}

// astring_list

struct astring_list* astring_split(struct arena *a, char *cstr, const char *sep) {
    struct astring_list *result = arena_push(a, sizeof(struct astring_list));
    *result = (struct astring_list){0};

    char *cursor = cstr+strspn(cstr, sep);
    if ('\0' == *cursor) {
        return result;
    }

    result->items = arena_top(a);
    while ('\0' != *cursor) {
        int size = strcspn(cursor, sep);
        astring_init_ln(a, cursor, size);
        ++result->size;
        cursor += size;
        cursor += strspn(cursor, sep);
    }
    return result;
}
