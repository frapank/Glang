#ifndef LLVM_RETURN_H
#define LLVM_RETURN_H

#include <llvm-c/Core.h>
struct variable;       // form llvm_var.h
struct node;           // from ast_types.h
struct function;       // from ast_types.h
struct LLVMTypeTable;  // from llvm_types.h

void llvm_return_generate_return(const LLVMBuilderRef builder,
                                 struct variable* variables,
                                 struct function* fun, const struct node* node,
                                 struct LLVMTypeTable types_table);
#endif
