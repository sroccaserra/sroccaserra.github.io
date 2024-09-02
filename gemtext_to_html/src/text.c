#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "text.h"
#include "arena.h"

bool starts_with(char *text, char *prefix) {
    if (text && prefix) {
        char *result = strstr(text, prefix);
        if (result && result == text) {
            return true;
        }
    }
    return false;
}

#define check_errno(str) do { \
    if(errno) {               \
        perror(str);          \
        exit(1);              \
    }                         \
} while (0)

long slurp(struct arena *a, char *filename, char **ptext) {
    errno = 0;
    FILE *file = fopen(filename, "r");
    check_errno(filename);
    assert(file);
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    char *buffer = arena_push(a, size + 1);
    errno = 0;
    (void)!fread(buffer, size, 1, file); // We don't need the result, (void)! avoids the warning
    check_errno(NULL);
    fclose(file);
    buffer[size] = '\0';

    *ptext = buffer;
    return size;
}
