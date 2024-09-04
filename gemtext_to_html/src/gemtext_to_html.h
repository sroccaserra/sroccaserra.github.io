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
    QUOTE,
    PREFORMATED_TOGGLE,
};

struct convert_state {
    bool is_in_preformated_mode;
    enum line_type previous_line_type;
};

char *convert(struct arena *a, struct convert_state *state, char *line);
void convert_input(struct arena *a, char *input, int file_size);

#endif
