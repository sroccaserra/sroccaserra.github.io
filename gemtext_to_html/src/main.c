#include <errno.h>
#include <stdio.h>
#include <unistd.h>

#include "arena.h"
#include "gemtext_to_html.h"
#include "options.h"
#include "text.h"

// Could be made configurable, to avoid having to rebuild for big files
#define ARENA_SIZE 1000000

int parse_options(int argc, char **argv, struct options *options) {
    int nb_args = 0;
    char opt;
    while (-1 != (opt = getopt(argc, argv, "c:"))) {
        switch(opt) {
            case 'c':
                options->img_class = optarg;
                nb_args += 2;
                break;
            default:
                fprintf(stderr, "Usage: %s [-c img_class] file\n",
                        argv[0]);
                exit(EXIT_FAILURE);
        }
    }
    return nb_args;
}

int main(int argc, char **argv) {
    int max_args = 2;
    struct options options = {0};
    max_args += parse_options(argc, argv, &options);
    assert(argc <= max_args);

    FILE *stream;
    if (argc == max_args - 1) {
        stream = stdin;
    } else {
        char * filename = argv[max_args - 1];
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
    convert_input(a, &options, input, file_size);

    arena_discard(a);
    return 0;
}
