#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "text.h"

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
    *s += strspn(*s, SPACES);
}

void skip_non_spaces(char **s) {
    *s += strcspn(*s, SPACES);
}
