#include <errno.h>
#include <stdio.h>

#include "arena.h"
#include "gemtext_to_html.h"
#include "text.h"

// Could be made configurable, to avoid having to rebuild for big files
#define ARENA_SIZE 1000000

int main(int argc, char **argv) {
    assert(argc <= 2);

    FILE *stream;
    if (argc == 1) {
        stream = stdin;
    } else {
        char * filename = argv[1];
        errno = 0;
        stream = fopen(filename, "r");
        if(errno) {
            perror(filename);
            exit(1);
        }
    }

    struct arena *a = arena_init(ARENA_SIZE);
    char *input;
    int file_size = slurp(a, stream, &input);
    convert_input(a, input, file_size);

    arena_discard(a);
    return 0;
}
