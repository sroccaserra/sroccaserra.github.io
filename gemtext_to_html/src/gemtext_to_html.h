#ifndef GEMTEXT_TO_HTML_H
#define GEMTEXT_TO_HTML_H

#include <stdbool.h>

#include "arena.h"

enum line_type {
    NONE,
    TEXT,
    HEADING,
    LINK,
    LIST_ITEM,
};

struct convert_state {
    bool is_in_list;
    bool is_in_quote;
    enum line_type previous_line_type;
};

char *convert(struct arena *a, struct convert_state *state, char *line);
void convert_input(struct arena *a, char *input, int file_size);

#endif
