#include "../../include/llvm_var.h"

#include <llvm-c/BitWriter.h>
#include <llvm-c/Core.h>
#include <llvm-c/Target.h>
#include <llvm-c/TargetMachine.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error_utils.h"

/* Var utils */
static struct variable* llvm_variable_add(struct variable** head, const char* name,
                                     LLVMValueRef ref, LLVMTypeRef type) 
{
    struct variable* var = malloc(sizeof(struct variable));
    if (!var) {
        fprintf(stderr, "[-] Failed to allocate memory for variable\n");
        exit(1);
    }
    snprintf(var->name, sizeof(var->name), "%s", name);
    var->ref = ref;
    var->next = *head;
    var->type = type;
    return var;
}

static LLVMTypeRef llvm_variable_find_type(struct variable* head, const char* name) 
{
    while (head) {
        if (strcmp(head->name, name) == 0) {
            return head->type;
        }
        head = head->next;
    }
    return NULL;
}

LLVMValueRef llvm_find_variable(struct variable* head, const char* name) 
{
    while (head) {
        if (strcmp(head->name, name) == 0) {
            return head->ref;
        }
        head = head->next;
    }
    return NULL;
}

/* Assign */
void llvm_var_assign_number(const struct node* node,
        struct variable** variables,
        const LLVMBuilderRef builder,
        const LLVMTypeRef type) 
{
    LLVMValueRef var = LLVMBuildAlloca(builder, type, node->name);
    LLVMValueRef value;

    if (node->use_identifier) {
        LLVMValueRef source = llvm_find_variable(*variables, node->identifier);
        LLVMTypeRef source_type = llvm_variable_find_type(*variables, node->identifier);

        if (!source) {
            send_syntax_error_by_line(node->full_line, node->column,
                                      "Variable used before declaration");
            exit(1);
        }

        if (source_type != type) {
            send_syntax_error_by_line(node->full_line, node->column,
                                      "Type mismatch in assignment");
            exit(1);
        }

        value = LLVMBuildLoad2(builder, type, source, "loadtmp");
    } else {
        value = LLVMConstInt(type, node->number, /* signExtend */ 0);
    }

    LLVMBuildStore(builder, value, var);
    *variables = llvm_variable_add(variables, node->name, var, type);
}

void llvm_var_assign_float(const struct node* node,
        struct variable** variables,
        const LLVMBuilderRef builder,
        const LLVMTypeRef float_type) 
{
    LLVMValueRef var = LLVMBuildAlloca(builder, float_type, node->name);
    LLVMValueRef value;

    if (node->use_identifier) {
        LLVMValueRef source = llvm_find_variable(*variables, node->identifier);
        LLVMTypeRef source_type = llvm_variable_find_type(*variables, node->identifier);

        if (!source) {
            send_syntax_error_by_line(node->full_line, node->column,
                                      "Variable used before declaration");
            exit(1);
        }

        if (source_type != float_type) {
            send_syntax_error_by_line(node->full_line, node->column,
                                      "Type mismatch in float assignment");
            exit(1);
        }

        value = LLVMBuildLoad2(builder, float_type, source, "loadtmp");
    } else {
        value = LLVMConstReal(float_type, node->floating);
    }

    LLVMBuildStore(builder, value, var);
    *variables = llvm_variable_add(variables, node->name, var, float_type);
}


/* Reassign */
void llvm_var_reassign_number(const struct node* node,
        struct variable** variables,
        const LLVMBuilderRef builder,
        const LLVMTypeRef type) 
{
    LLVMValueRef var = llvm_find_variable(*variables, node->name);
    LLVMTypeRef original_type = llvm_variable_find_type(*variables, node->name);
    if (!var) {
        send_syntax_error_by_line(node->full_line, node->column,
                                  "Variable used before declaration");
        exit(1);
    }
    if (original_type != type) {
        send_syntax_error_by_line(node->full_line, node->column,
                                  "Wrong declaration for variable");
        exit(1);
    }
    LLVMBuildStore(builder, LLVMConstInt(type, node->number, 0), var);
}

void llvm_var_reassign_float(const struct node* node,
        struct variable** variables,
        const LLVMBuilderRef builder,
        const LLVMTypeRef float_type) 
{
    LLVMValueRef var = llvm_find_variable(*variables, node->name);
    LLVMTypeRef type = llvm_variable_find_type(*variables, node->name);
    if (!var) {
        send_syntax_error_by_line(node->full_line, node->column,
                                  "Variable used before declaration");
        exit(1);
    }
    if (type != float_type) {
        send_syntax_error_by_line(node->full_line, node->column,
                                  "Wrong declaration for variable");
        exit(1);
    }
    LLVMBuildStore(builder, LLVMConstReal(float_type, node->floating), var);
}

