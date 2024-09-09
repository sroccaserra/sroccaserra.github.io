#ifndef TEXT_H
#define TEXT_H

#include <stdbool.h>
#include <stdio.h>

#include "arena.h"

#define SPACES " \f\n\r\t\v"

bool starts_with(char *text, char *prefix);
bool is_empty(char *line);

long slurp(struct arena *a, FILE *file, char **ptext);

#define print(fmt, ...) (printf(fmt"\n", __VA_ARGS__))

#endif
