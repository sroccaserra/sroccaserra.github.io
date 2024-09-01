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
