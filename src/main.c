#include "compiler.h"
#include "compiler_opts.h"

int main(int argc, char** argv) 
{
    if(compiler_opts_init(argc, argv)) 
        return 1;
        
    compile_file();
}
