#ifndef AST_TYPES
#define AST_TYPES

#include <stdbool.h>

#define MAX_LINE_LEN 1024
#define MAX_IDENTIFIER_LENGTH 256

enum argument_type {
    ARG_INT,
    ARG_FLOAT,
    ARG_CHAR,
};

struct argument {
    enum argument_type type;
    union {
        int i;
        float f;
        char str;
    };
};

enum node_type {
    NO_BODY,

    NO_ADD,
    NO_SUB,
    NO_MUL,
    NO_DIV,
    NO_INCREMENT,

    NO_REASSIGN_INT,
    NO_REASSIGN_FLOAT,
    NO_REASSIGN_CHAR,

    NO_ASSIGN_INT,
    NO_ASSIGN_FLOAT,
    NO_ASSIGN_CHAR,

    NO_PRINT,
    NO_RETURN,
    NO_ASM,

    NO_IF,
    NO_MAJOR,
    NO_MINOR,
    NO_EQUAL_TO,

    NO_WHILE,
    NO_FOR,
    NO_FUNCALL
};

struct node {
    enum node_type type;
    struct node* lnode;
    struct node* rnode;

    struct node* code;  // IF, FOR
    struct node* then;  // IF or FOR body
    struct node* els;   // ELSE
    struct node* init;  // INIT FOR
    struct node* inc;   // INCREMENT FOR

    struct node* body;  // Point to the first node
    struct node* next;  // Point to the next node

    char name[MAX_IDENTIFIER_LENGTH];  // Name of var or Name of text
    bool use_identifier;
    union {
        char letter;     // Just for chars
        int number;      // only for NO_NUM or NO_RETURN
        float floating;  // only for NO_NUM or NO_RETURN
        char identifier[MAX_IDENTIFIER_LENGTH];
    };

    char full_line[MAX_LINE_LEN];
    int column;
};

enum function_return_type { RET_INT, RET_CHAR, RET_FLOAT, RET_VOID };

struct function {
    enum function_return_type return_type;
    struct node* body;
    int node_count;
    struct argument* arguments;
    char name[MAX_IDENTIFIER_LENGTH];
};

struct function_list {
    struct function** functions;
    int count;
};

#endif
