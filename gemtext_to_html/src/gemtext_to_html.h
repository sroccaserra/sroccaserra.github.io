#ifndef GEMTEXT_TO_HTML_H
#define GEMTEXT_TO_HTML_H

#include <stdbool.h>

#include "arena.h"
#include "options.h"

enum line_type {
    NONE,
    TEXT,
    EMPTY_LINE,
    HEADING,
    LINK,
    LINK_TO_IMAGE,
    LIST_ITEM,
    QUOTE,
    PREFORMATED_TOGGLE,
};

struct convert_state {
    bool is_in_preformated_mode;
    enum line_type previous_line_type;
};

char *convert(struct arena *a, struct options *o, struct convert_state *state, char *line);
void convert_input(struct arena *a, struct options *o, char *input, int file_size);

#endif
