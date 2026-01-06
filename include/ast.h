#ifndef AST_H
#define AST_H

#include "ast_types.h"
struct token;

struct node* ast_transform_into_node(const struct token* tokens, int* current_index);
struct function* ast_get_function_by_name(const char* name, struct function_list function_list);
struct argument* ast_parse_param(const struct token* tokens, int first_param_index);
struct function ast_parse_function(const struct token* tokens, int* current_index);
void ast_add_function_to_list(struct function* fun, struct function_list* function_list);

#endif
