#ifndef ARGS_MANAGER_H
#define ARGS_MANAGER_H

struct compiler_opts {
    char output_name[256];
    char file_name[256];
};

struct compiler_opts compiler_opts_get();
int compiler_opts_init(int argc, const char* argv[]);

#endif
