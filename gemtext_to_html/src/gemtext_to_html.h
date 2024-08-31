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

static bool is_link(char *line) {
    return starts_with(line, "=>");
}

// Could be made configurable, or arena could be injected, or made static
#define ARENA_SIZE_FOR_LINKS 128

static char *link_to_a(struct arena *a, char *line) {
    struct arena *tmp = arena_init(ARENA_SIZE_FOR_LINKS);

    char *start = line + 2;
    start += strspn(start, " ");
    struct astring_list *words = astring_split(tmp, start, spaces);
    assert(words->size);

    struct astring *url = &words->items[0];
    struct astring *description;
    if (words->size == 1) {
        description = url;
    } else {
        char *description_start = start + url->size;
        description_start += strspn(description_start, spaces);
        description = astring_init(tmp, description_start);
    }

    struct astring *link_pre = astring_init(tmp, "<a href=\"");
    struct astring *link_mid = astring_init(tmp, "\">");
    struct astring *link_suf = astring_init(tmp, "</a>");
    int size = link_pre->size + url->size + link_mid->size + description->size + link_suf->size;
    char *result = arena_push(a, size + 1);
    char *cstr = result;
    cstr += astring_sprint(link_pre, cstr);
    cstr += astring_sprint(url, cstr);
    cstr += astring_sprint(link_mid, cstr);
    cstr += astring_sprint(description, cstr);
    cstr += astring_sprint(link_suf, cstr);
    result[size] = '\0';

    arena_discard(tmp);
    return result;
}

char *convert(struct arena *a, char *line) {
    if (is_link(line)) {
        return link_to_a(a, line);
    } else {
        return line;
    }
}

#endif
