#include "compiler.h"
#include "compiler_opts.h"

int main(int argc, const char* argv[]) 
{
    compiler_opts_init(argc, argv);
    struct compiler_opts flags = compiler_opts_get();

    compile_file(flags.file_name, flags.output_name);
}
