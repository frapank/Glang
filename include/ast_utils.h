#ifndef AST_UTILS_H
#define AST_UTILS_H

#include "lexer.h"
#include "common.h"

#define EXPECT(tokens, idx, expected, msg)                        \
    do {                                                          \
        if ((tokens)[idx].type != (expected))                     \
            token_failed(tokens, idx, (msg), __FILE__, __LINE__); \
    } while (0)

NORETURN void ast_token_failed(const struct token* tokens,
        int index,
        const char* msg,
        const char* file,
        int line);

NORETURN void ast_allocation_failed(const int line);

void ast_check_if_allocated(const void* ptr, const int line);

#endif
