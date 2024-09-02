#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "text.h"
#include "arena.h"
#include "astring.h"
#include "gemtext_to_html.h"

static bool is_link(char *line) {
    return starts_with(line, "=>");
}

static bool is_heading(char *line) {
    return starts_with(line, "#");
}

static bool is_list_item(char *line ) {
    return starts_with(line, "*");
}

struct text_chunk {
    int size;
    char *pos;
};

static char *text_to_html(struct arena *a, char *line) {
    char *result = arena_top(a);

    struct text_chunk input;
    struct text_chunk output;
    char *cursor;
    input.pos = line;
    cursor = result;

    while ('\0' != *input.pos) {
        switch (*input.pos) {
            case '&':
                input.size = 1;
                output.pos = "&amp;";
                output.size = 5;
                break;
            case '<':
                input.size = 1;
                output.pos = "&lt;";
                output.size = 4;
                break;
            case '>':
                input.size = 1;
                output.pos = "&gt;";
                output.size = 4;
                break;
            default:
                input.size = strcspn(input.pos, "&<>");
                output = input;
        }
        arena_push(a, output.size);
        strncpy(cursor, output.pos, output.size);
        input.pos += input.size;
        cursor += output.size;
    }
    arena_push(a, 5);
    strncpy(cursor, "<br/>", 5);
    cursor += 5;
    int size = cursor - result;
    result[size] = '\0';

    return result;
}

// Could be made configurable, or arena could be injected, or made static
#define ARENA_SIZE_FOR_LINKS 128

#define LINK_PRE "<a href=\""
#define LINK_MID "\">"
#define LINK_SUF "</a>"

static char *link_to_a(struct arena *a, char *line) {
    struct arena *tmp = arena_init(ARENA_SIZE_FOR_LINKS);

    char *url_start = line + 2;
    url_start += strspn(url_start, SPACES);
    int url_size = strcspn(url_start, SPACES);
    struct astring *url = astring_init_ln(tmp, url_start, url_size);

    struct astring *description;
    {
        char *description_start = url_start + url_size;
        description_start += strspn(description_start, SPACES);
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

char *heading_to_html(struct arena *a, char *line) {
    char *result = arena_top(a);
    int level = strspn(line, "#");
    assert(1 <= level);
    assert(level <= 6);
    char *start = line+level;
    start += strspn(start, SPACES);
    int size = sprintf(result, "<h%d>%s</h%d>", level, start, level);
    arena_push(a, size+1);
    result[size] = '\0';
    return result;
}

char *list_item_to_html(struct arena *a, char *line) {
    char *result = arena_top(a);
    char *start = line+strspn(line, "*");
    start += strspn(start, SPACES);
    int size = sprintf(result, "<li>%s</li>", start);
    arena_push(a, size+1);
    result[size] = '\0';
    return result;
}

char *convert(struct arena *a, char *line) {
    if (is_link(line)) {
        return link_to_a(a, line);
    } else if (is_heading(line)) {
        return heading_to_html(a, line);
    } else if (is_list_item(line)) {
        return list_item_to_html(a, line);
    } else {
        return text_to_html(a, line);
    }
}

void convert_input(struct arena *a, char *input, int file_size) {
    int total_bytes_seen = 0;
    char *line = input;
    bool is_in_list = false;
    while (total_bytes_seen < file_size) {
        if (is_list_item(line)) {
            if (!is_in_list) {
                printf("<ul>\n");
                is_in_list = true;
            }
        } else {
            if (is_in_list) {
                printf("</ul>\n");
                is_in_list = false;
            }
        }
        int line_size = strcspn(line, "\n");
        line[line_size] = '\0';
        printf("%s\n", convert(a, line));
        line += line_size + 1;
        total_bytes_seen += line_size + 1;
    }
}
