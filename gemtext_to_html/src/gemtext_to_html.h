#ifndef GEMTEXT_TO_HTML_H
#define GEMTEXT_TO_HTML_H

#include "arena.h"

char *convert(struct arena *a, char *line);
void convert_input(struct arena *a, char *input, int file_size);

#endif
