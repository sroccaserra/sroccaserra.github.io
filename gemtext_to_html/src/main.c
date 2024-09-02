#include <stdio.h>

#include "arena.h"
#include "gemtext_to_html.h"
#include "text.h"

// Could be made configurable, to avoid having to rebuild for big files
#define ARENA_SIZE 1000000

int main(int argc, char **argv) {
    assert(2 == argc);

    struct arena *a = arena_init(ARENA_SIZE);
    char *input;
    int file_size = slurp(a, argv[1], &input);

    convert_input(a, input, file_size);

    arena_discard(a);
    return 0;
}
