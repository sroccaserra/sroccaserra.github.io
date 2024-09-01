#ifndef TEXT_H
#define TEXT_H

#include <stdbool.h>

#define SPACES " \f\n\r\t\v"

bool starts_with(char *text, char *prefix);
void skip_spaces(char **s);
void skip_non_spaces(char **s);

#define print(fmt, ...) (printf(fmt"\n", __VA_ARGS__))

#endif
