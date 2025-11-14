#ifndef ARGS_MANAGER_H
#define ARGS_MANAGER_H


struct Flags {
    char output_name[256];
    char file_name[256];
};

struct Flags get_arguments_flags(int argc, const char* argv[]);

#endif
