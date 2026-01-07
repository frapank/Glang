#include "compiler_opts.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static _Bool initialized = 0;
static struct compiler_opts copts;

const struct compiler_opts* compiler_opts_get(void)
{
    if(!initialized) {
        fprintf(stderr, "args_get called before init\n");
        _Exit(EXIT_FAILURE);
    }
    return &copts;
}

int compiler_opts_init(int argc, char** argv)
{
    char c;
    while((c = getopt(argc, argv, "o:")) != -1) {
        switch(c) {
            case 'o':
                snprintf(copts.output_path, sizeof(copts.output_path), "%s", optarg);
                copts.output_path_present = 1;
                break;
            default:
                printf("[-] Invalid compiler option: -%c\n", c);
                return 1;
        }
    }

    copts.num_files = argc - optind;
    copts.files = argv + optind;

    if(copts.num_files <= 0) {
        printf("[-] No file specified: glang [OPTIONS] <FILES>\n");
        return 1;
    }

    snprintf(copts.file_path, sizeof(copts.file_path), "%s", copts.files[0]); /* TEMP */

#ifdef _WIN32
    fprintf(stderr, "[-] Not implemented yet on windows...");
    _Exit(EXIT_FAILURE);
#endif

    initialized = 1;
    return 0;
}

