#ifndef ASTRING_H
#define ASTRING_H

#include <stdbool.h>

#include "arena.h"

// "astring" is for "arena string". "string" would be good, but the header file
// "string.h" would be confusing, "astring.h" is not.
//
// Conventions
// "cstr" is a usual null-terminated C string.
// "s" stands for a "struct astring"
// "a" stands for "arena"
// "ln" is for "length"

struct astring {
    int size;
    char *items;
};

struct astring *astring_init(struct arena *a, char *cstr);
struct astring *astring_init_ln(struct arena *a, char *cstr, int size);

void astring_set_cstr(struct astring *self, char *cstr);
void astring_set_cstr_ln(struct astring *self, char *cstr, int size);
bool astring_is_same(struct astring *self, char *cstr);
char *astring_to_cstr(struct arena *a, struct astring *self);
int astring_sprint(struct astring *self, char *buffer);

// astring_list

struct astring_list {
    int size;
    struct astring *items;
};

struct astring_list* astring_split(struct arena *a, char *cstr, const char *sep);
#endif
