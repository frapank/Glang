#include <stddef.h>

#include "compiler.h"
#include "compiler_opts.h"

int main_real(int argc, char *argv[])
{
    if (compiler_opts_init(argc, argv))
        return 1;

    compile_file();
    return 0;
}

#ifdef _MSC_VER

#include <stdlib.h>
#include <wchar.h>

int wmain(int argc, wchar_t *wargv[])
{
    char **argv = malloc(sizeof(*argv) * (size_t)argc);
    if (!argv) return 1;

    for (int i = 0; i < argc; ++i)
        argv[i] = win_utf16to8(wargv[i]);

    int ret = main_real(argc, argv);

    for (int i = 0; i < argc; ++i)
        free(argv[i]);
    free(argv);

    return ret;
}

#else

int main(int argc, char *argv[])
{
    return main_real(argc, argv);
}

#endif

