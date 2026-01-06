#ifndef LLVM_GENERATOR_H
#define LLVM_GENERATOR_H

#include <llvm-c/Core.h>
struct function;

void llvm_generator_function_ir(struct function* fun,
                                 const LLVMModuleRef* module);

#endif
