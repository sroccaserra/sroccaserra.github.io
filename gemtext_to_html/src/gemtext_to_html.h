#ifndef GEMTEXT_TO_HTML_H
#define GEMTEXT_TO_HTML_H

#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "text.h"
#include "arena.h"
#include "astring.h"

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
    struct arena a = arena_init(128);

    char *start = line + 2;
    start += strspn(start, " ");
    struct astring_list *words = astring_split(&a, start, spaces);
    assert(words->size);

    struct astring *url = &words->items[0];
    struct astring *description;
    if (words->size == 1) {
        description = url;
    } else {
        char *description_start = start + url->size;
        description_start += strspn(description_start, spaces);
        description = astring_init(&a, description_start);
    }

    struct astring *link_pre = astring_init(&a, "<a href=\"");
    struct astring *link_mid = astring_init(&a, "\">");
    struct astring *link_suf = astring_init(&a, "</a>");
    int size = link_pre->size + url->size + link_mid->size + description->size + link_suf->size;
    char *result = malloc(size + 1);
    char *cstr = result;
    cstr += astring_sprint(link_pre, cstr);
    cstr += astring_sprint(url, cstr);
    cstr += astring_sprint(link_mid, cstr);
    cstr += astring_sprint(description, cstr);
    cstr += astring_sprint(link_suf, cstr);
    result[size] = '\0';

    arena_discard(&a);
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
