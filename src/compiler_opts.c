#include "compiler_opts.h"

#include <stdlib.h>
#include <stdio.h>
#include "error_utils.h"

static int initialized = 0;
static struct compiler_opts copts;

struct compiler_opts compiler_opts_get()
{
    if(!initialized) {
        fprintf(stderr, "args_get called before init\n");
        _Exit(EXIT_FAILURE);
    }
    return copts;
}

int compiler_opts_init(int argc, const char* argv[])
{
    /* TODO */
    (void)argc;
    (void)argv;
    return 0;
}

