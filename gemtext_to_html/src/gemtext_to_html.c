#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "text.h"
#include "arena.h"
#include "gemtext_to_html.h"

static bool is_link(char *line) {
    return starts_with(line, "=>");
}

static bool is_heading(char *line) {
    return *line == '#';
}

static bool is_list_item(char *line ) {
    return *line == '*';
}

static bool is_quote(char *line) {
    return *line == '>';
}

static bool is_preformated_toggle(char *line) {
    return starts_with(line, "```");
}

struct text_chunk {
    int size;
    char *pos;
};

static void text_to_html(struct arena *a, char *line) {
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
    int size = cursor - result;
    result[size] = '\0';
}

static void empty_line(struct arena *a) {
    char *result = arena_push(a, 1);
    *result = '\0';
}

static const char LINK_PRE[] = "<li><a href=\"";
static const char LINK_MID[] = "\">";
static const char LINK_SUF[] = "</a></li>";

static void link_to_a(struct arena *a, char *line) {
    char *result = arena_top(a);

    char *url_start = line + 2;
    url_start += strspn(url_start, SPACES);
    int url_size = strcspn(url_start, SPACES);

    char *description_start = url_start + url_size;
    description_start += strspn(description_start, SPACES);
    int description_size = strlen(description_start);
    if (description_size == 0) {
        description_start = url_start;
        description_size = url_size;
    }

    arena_append(a, LINK_PRE, sizeof(LINK_PRE) - 1);
    arena_append(a, url_start, url_size);
    arena_append(a, LINK_MID, sizeof(LINK_MID) - 1);
    arena_append(a, description_start, description_size);
    arena_append(a, LINK_SUF, sizeof(LINK_SUF) - 1);

    int size = (char *)arena_top(a) - result ;
    result[size] = '\0';
}

static void link_to_img(struct arena *a, char *img_class, char *line) {
    char *result = arena_top(a);
    arena_append(a, "<img ", 5);
    if (img_class) {
        arena_append(a, "class=\"", 7);
        arena_append(a, img_class, strlen(img_class));
        arena_append(a, "\" ", 2);
    }
    arena_append(a, "src=\"", 5);

    char *url_start = line + 2;
    url_start += strspn(url_start, SPACES);
    int url_size = strcspn(url_start, SPACES);
    arena_append(a, url_start, url_size);

    arena_append(a, "\" />", 4);
    int size = (char *)arena_top(a) - result ;
    result[size] = '\0';
}

static void heading_to_html(struct arena *a, char *line) {
    char *result = arena_top(a);
    int level = strspn(line, "#");
    assert(1 <= level);
    assert(level <= 6);
    char *start = line+level;
    start += strspn(start, SPACES);
    int size = sprintf(result, "<h%d>%s</h%d>", level, start, level);
    arena_push(a, size+1);
    result[size] = '\0';
}

static void list_item_to_html(struct arena *a, char *line) {
    char *result = arena_top(a);
    char *start = line+strspn(line, "*");
    start += strspn(start, SPACES);
    int size = sprintf(result, "<li>%s</li>", start);
    arena_push(a, size+1);
    result[size] = '\0';
}

static void quote_to_html(struct arena *a, char *line) {
    char *start = line + 1;
    start += strspn(start, SPACES);
    text_to_html(a, start);
}

static void preformated_begin(struct arena *a) {
    int output_size = 6;
    char *result = arena_push(a, output_size);
    strncpy(result, "<pre>", output_size);
}

static void preformated_end(struct arena *a) {
    int output_size = 7;
    char *result = arena_push(a, output_size);
    strncpy(result, "</pre>", output_size);
}

static enum line_type line_type_for(char *line) {
    if (is_link(line)) {
        if (ends_with(line, ".png") || ends_with(line, ".jpg") || ends_with(line, ".jpeg")) {
            return LINK_TO_IMAGE;
        }
        return LINK;
    } else if (is_heading(line)) {
        return HEADING;
    } else if (is_list_item(line)) {
        return LIST_ITEM;
    } else if (is_quote(line)) {
        return QUOTE;
    } else if (is_preformated_toggle(line)) {
        return PREFORMATED_TOGGLE;
    } else if (is_empty(line)) {
        return EMPTY_LINE;
    }

    return TEXT;
}

#define is_starting_type(type, state, line_type) (type != state->previous_line_type && type == line_type)
#define is_ending_type(type, state, line_type) (type == state->previous_line_type && type != line_type)

char *convert(struct arena *a, struct options *o, struct convert_state *state, char *line) {
    enum line_type line_type = line_type_for(line);

    if (state->is_in_preformated_mode && line_type != PREFORMATED_TOGGLE) {
        return line;
    }

    char *result = arena_top(a);

    if (is_ending_type(TEXT, state, line_type)) {
        arena_append(a, "</p>\n", 5);
    } else if (is_ending_type(LIST_ITEM, state, line_type)) {
        arena_append(a, "</ul>\n", 6);
    } else if (is_ending_type(QUOTE, state, line_type)) {
        arena_append(a, "</blockquote>\n", 14);
    } else if (is_ending_type(LINK, state, line_type)) {
        arena_append(a, "</ul>\n", 6);
    }


    if (is_starting_type(TEXT, state, line_type)) {
        arena_append(a, "<p>\n", 4);
    } else if (TEXT == line_type) {
        arena_append(a, "<br/>\n", 6);
    }

    if (is_starting_type(LIST_ITEM, state, line_type)) {
        arena_append(a, "<ul>\n", 5);
    }

    if (is_starting_type(QUOTE, state, line_type)) {
        arena_append(a, "<blockquote>\n", 13);
    } else if (QUOTE == line_type) {
        arena_append(a, "<br/>\n", 6);
    }

    if (is_starting_type(LINK, state, line_type)) {
        arena_append(a, "<ul>\n", 5);
    }

    switch (line_type) {
        case NONE:
            assert(false);
            break;
        case LINK:
            link_to_a(a, line);
            break;
        case LINK_TO_IMAGE:
            link_to_img(a, o->img_class, line);
            break;
        case HEADING:
            heading_to_html(a, line);
            break;
        case LIST_ITEM:
            list_item_to_html(a, line);
            break;
        case QUOTE:
            quote_to_html(a, line);
            break;
        case PREFORMATED_TOGGLE:
            if (!state->is_in_preformated_mode) {
                state->is_in_preformated_mode = true;
                preformated_begin(a);
            } else {
                preformated_end(a);
                state->is_in_preformated_mode = false;
            }
            break;
        case TEXT:
            text_to_html(a, line);
            break;
        case EMPTY_LINE:
            empty_line(a);
            break;
        default:
            assert(false);
    }

    state->previous_line_type = line_type;
    return result;
}

static void close_pending_tags(enum line_type last_line_type) {
    switch (last_line_type) {
        case LINK:
            printf("</ul>\n");
            break;
        case LIST_ITEM:
            printf("</ul>\n");
            break;
        case QUOTE:
            printf("</blockquote>\n");
            break;
        case TEXT:
            printf("</p>\n");
            break;
        case LINK_TO_IMAGE:
        case HEADING:
        case NONE:
        case PREFORMATED_TOGGLE:
        case EMPTY_LINE:
            break;
        default:
            assert(false);
    }
}

void convert_input(struct arena *a, struct options *o, char *input, int file_size) {
    int total_bytes_seen = 0;
    char *line = input;
    struct convert_state state = {0};
    while (total_bytes_seen < file_size) {
        int line_size = strcspn(line, "\n");
        line[line_size] = '\0';
        printf("%s\n", convert(a, o, &state, line));
        line += line_size + 1;
        total_bytes_seen += line_size + 1;
    }

    close_pending_tags(state.previous_line_type);
}
