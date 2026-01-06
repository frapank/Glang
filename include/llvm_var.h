#ifndef LLVM_VAR_H
#define LLVM_VAR_H

#include <llvm-c/Core.h>
#include "ast_types.h"

struct variable {
    char name[256];
    LLVMValueRef ref;
    LLVMTypeRef type;
    struct variable* next;
};

LLVMValueRef llvm_find_variable(struct variable* head, const char* name);

/* Assign */
void llvm_var_assign_number(const struct node* node, struct variable** variables,
                         const LLVMBuilderRef builder,
                         const LLVMTypeRef int_type);

void llvm_var_assign_float(const struct node* node, struct variable** variables,
                           const LLVMBuilderRef builder,
                           const LLVMTypeRef float_type);

/* Reassign */
void llvm_var_reassign_number(const struct node* node, struct variable** variables,
                           const LLVMBuilderRef builder,
                           const LLVMTypeRef int_type);

void llvm_var_reassign_float(const struct node* node,
                             struct variable** variables,
                             const LLVMBuilderRef builder,
                             const LLVMTypeRef float_type);

#endif
