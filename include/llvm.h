#ifndef LLVM_H
#define LLVM_H

#include <stdbool.h>
struct function_list; //ast_types.h

void llvm_generate(struct function_list function_list, const char* output_file);

#endif
