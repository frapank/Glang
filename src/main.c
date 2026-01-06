#include "compiler.h"
#include "compiler_opts.h"

int main(int argc, const char* argv[]) 
{
    compiler_opts_init(argc, argv);

    compile_file();
}
