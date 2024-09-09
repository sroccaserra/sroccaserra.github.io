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

bool is_empty(char *line) {
    char *start = line + strspn(line, SPACES);
    return '\0' == *start;
}

#define check_errno(str) do { \
    if(errno) {               \
        perror(str);          \
        exit(1);              \
    }                         \
} while (0)

long slurp(struct arena *a, FILE *file, char **ptext) {
    assert(file);
    long size = 0;
    int chunk_size = 256;
    char *buffer = arena_push(a, chunk_size);
    char *buffer_pos = buffer;
    int read_size = 0;

    errno = 0;
    while (0 != (read_size = fread(buffer_pos, 1, chunk_size, file))) {
        check_errno(NULL);
        size += read_size;
        buffer_pos += read_size;
        arena_push(a, chunk_size);
    }

    fclose(file);
    buffer[size] = '\0';

    *ptext = buffer;
    return size;
}
