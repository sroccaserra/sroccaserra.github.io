#ifndef TEXT_H
#define TEXT_H

#include <stdbool.h>
#include <stdio.h>

#include "arena.h"

#define SPACES " \f\n\r\t\v"

bool starts_with(char *text, char *prefix);
long slurp(struct arena *a, char *filename, char **ptext);

#define print(fmt, ...) (printf(fmt"\n", __VA_ARGS__))

#endif
