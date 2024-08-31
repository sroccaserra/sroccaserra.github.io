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

#define LINK_PRE "<a href=\""
#define LINK_MID "\">"
#define LINK_SUF "</a>"

static char *link_to_a(struct arena *a, char *line) {
    struct arena *tmp = arena_init(ARENA_SIZE_FOR_LINKS);

    char *url_start = line + 2;
    url_start += strspn(url_start, spaces);
    int url_size = strcspn(url_start, spaces);
    struct astring *url = astring_init_ln(tmp, url_start, url_size);

    struct astring *description;
    {
        char *description_start = url_start + url_size;
        description_start += strspn(description_start, spaces);
        int description_size = strlen(description_start);
        if (description_size == 0) {
            description = url;
        } else {
            description = astring_init_ln(tmp, description_start, description_size);
        }
    }

    struct astring *link_pre = astring_init(tmp, LINK_PRE);
    struct astring *link_mid = astring_init(tmp, LINK_MID);
    struct astring *link_suf = astring_init(tmp, LINK_SUF);
    int size = link_pre->size + url->size + link_mid->size + description->size + link_suf->size;
    char *result = arena_push(a, size + 1);
    {
        char *cstr = result;
        cstr += astring_sprint(link_pre, cstr);
        cstr += astring_sprint(url, cstr);
        cstr += astring_sprint(link_mid, cstr);
        cstr += astring_sprint(description, cstr);
        cstr += astring_sprint(link_suf, cstr);
        result[size] = '\0';
    }

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
