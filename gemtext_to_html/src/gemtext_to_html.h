#ifndef GEMTEXT_TO_HTML_H
#define GEMTEXT_TO_HTML_H

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "text.h"

/*
 * Questions
 *
 * Some strlen are begining to crop up, do I need a type like
 * `struct string {int size; char *cstr;}`?
 *
 * Memory allocation start happening for the result, do I need an arena
 * already?
 */

static bool is_link(char *line) {
    return starts_with(line, "=>");
}

#define MAX_LINK_SIZE 1000

static char *link_to_a(char *line) {
    char *url = line + 2;
    skip_spaces(&url);
    assert('\0' != *url);

    char *description = url;
    skip_non_spaces(&description);
    if ('\0' == *description) {
        description = url;
    }
    else {
        while (isspace(*description)) {
            ++description;
        }
    }

    char *result = malloc(MAX_LINK_SIZE);
    snprintf(result, MAX_LINK_SIZE, "<a href=\"%s\">%s</a>", url, description);
    return result;
}

char *convert(char *line) {
    if (is_link(line)) {
        return link_to_a(line);
    } else {
        return line;
    }
}

#endif
