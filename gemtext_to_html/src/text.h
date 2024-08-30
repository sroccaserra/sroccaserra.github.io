#ifndef TEXT_H
#define TEXT_H

#include <ctype.h>
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

void skip_spaces(char **s) {
    while (isspace(**s) && '\0' != **s) {
        ++*s;
    }
}

void skip_non_spaces(char **s) {
    while (!isspace(**s) && '\0' != **s) {
        ++*s;
    }
}

#define print(fmt, ...) (printf(fmt"\n", __VA_ARGS__))

#endif
