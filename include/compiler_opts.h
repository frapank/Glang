#ifndef ARGS_MANAGER_H
#define ARGS_MANAGER_H

struct compiler_opts {
    char output_path[256];
    char file_path[256];
};

const struct compiler_opts* compiler_opts_get();
int compiler_opts_init(int argc, const char* argv[]);

#endif
