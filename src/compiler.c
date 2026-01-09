#include "compiler.h"

#include <stdlib.h>
#include "ast.h"
#include "llvm.h"
#include "lexer_utils.h"
#include "compiler_opts.h"
#include "common.h"

NORETURN static void compiler_file_not_found_error(const char* file_path) 
{
    if (file_path == NULL)
        fprintf(stderr, "[-] You should specify an argument \n");
    else
        fprintf(stderr, "[-] Can't find the file %s \n", file_path);
    exit(1);
}


NORETURN static void compiler_memory_allocation_error(void) 
{
    fprintf(stderr, "[-] Can't allocate memory \n");
    exit(1);
}

static struct token* compiler_get_tokens(const char* file_path) 
{
    FILE* file = fopen(file_path, "r");
    if (!file) compiler_file_not_found_error(file_path);
    struct token* tokens = token_process(file);
    fclose(file);

    #ifdef DEBUG
    printf("\n[debug] Generated tokens:\n");
    for (int i = 0; tokens[i].type != TOKEN_OEF; i++) {
        printf("  [%02d] %s, %s\n", i, tokens[i].value,
               token_type_to_string(tokens[i].type));
    }
    printf("\n");
    #endif

    return tokens;
}

static struct function_list compiler_parse_functions(const struct token* tokens) 
{
    struct function_list function_list = {.functions = NULL, .count = 0};
    int current_index = 0;
    while (tokens[current_index].type != TOKEN_OEF) {
        const struct token current_token = tokens[current_index];
        // Check for valid return type and parse the function
        if ((current_token.type == TOKEN_FUNCTION) &&
            tokens[current_index + 1].type == TOKEN_IDENTIFIER &&
            tokens[current_index + 2].type == TOKEN_LPAREN) {
            struct function* fun = calloc(1, sizeof(struct function));
            if (fun == NULL) compiler_memory_allocation_error();
            *fun = ast_parse_function(tokens, &current_index);
            ast_add_function_to_list(fun, &function_list);
        } else {
            current_index++;
        }
    }

    return function_list;
}

void compile_file(void) 
{
    const struct compiler_opts* copts = compiler_opts_get();
    printf("[+] Generating tokens... \n");
    const struct token* tokens = compiler_get_tokens(copts->file_path);
    printf("[+] Parsing tokens... \n");
    const struct function_list function_list = compiler_parse_functions(tokens);
    printf("[+] Generating llvm... \n");
    llvm_generate(function_list, copts->output_path);
}
