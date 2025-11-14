#ifndef LLVM_H
#define LLVM_H

#include <stdbool.h>
struct Function_list; //ast_types.h

void generate_llvm(struct Function_list function_list, const char* output_file);

#endif
