#ifndef TEXT_H
#define TEXT_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool starts_with(char *text, char *prefix) {
    if (text && prefix) {
        char *result = strstr(text, prefix);
        if (result && result == text) {
            return true;
        }
    }
    return false;
}

static const char *spaces = " \f\n\r\t\v";

void skip_spaces(char **s) {
    *s += strspn(*s, spaces);
}

void skip_non_spaces(char **s) {
    *s += strcspn(*s, spaces);
}

#define print(fmt, ...) (printf(fmt"\n", __VA_ARGS__))

#endif
