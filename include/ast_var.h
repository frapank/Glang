#ifndef VAR_H
#define VAR_H

struct token;  // From lexer.h
struct node;   // From ast_types.h

struct node* ast_var_assign_char(const struct token* tokens, 
        int* current_index, struct node* node);

struct node* ast_var_assign_int(const struct token* tokens, 
        int* current_index, struct node* node);

struct node* ast_var_assign_float(const struct token* tokens, 
        int* current_index, struct node* node);

struct node* ast_var_reassign_int(const struct token* tokens, 
        int* current_index, struct node* node);

struct node* ast_var_reassign_float(const struct token* tokens, 
        int* current_index, struct node* node);

struct node* ast_var_reassign_char(const struct token* tokens, 
        int* current_index, struct node* node);

struct node* ast_var_assign_let(const struct token* tokens, 
        int* current_index, struct node* node);

#endif
