#ifndef ARGS_MANAGER_H
#define ARGS_MANAGER_H

struct compiler_opts {
    char **files;
    int num_files;
    _Bool output_path_present;
    char output_path[256];
    char file_path[256]; /* TEMP */
};

const struct compiler_opts* compiler_opts_get(void);
int compiler_opts_init(int argc, char** argv);

#endif
