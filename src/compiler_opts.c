#include "compiler_opts.h"

#include <stdlib.h>
#include <stdio.h>

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

int compiler_opts_init(int argc, const char* argv[])
{
    /* TODO */
    (void)argc;
    (void)argv;
    return 0;
}

