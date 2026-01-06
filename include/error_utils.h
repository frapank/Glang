#ifndef ERROR_UTILS_H
#define ERROR_UTILS_H

struct token;  // form lexer.h

void send_syntax_error(const struct token* token, const char* error);
void send_syntax_error_by_line(const char* line, const int column,
                                      const char* error);
#endif
