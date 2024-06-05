#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum s_token_type
{
    T_IDENTIFIER,
    T_PIPE,
    T_GREAT,
    T_LESS,
    T_DLESS,
    T_DGREAT,
    T_AND,
    T_OR
} t_token_type;

typedef enum s_node_type
{
    N_COMMAND,
    N_PIPE,
    N_GREAT,
    N_LESS,
    N_DLESS,
    N_DGREAT,
    N_AND,
    N_OR
} t_node_type;

typedef struct s_token
{
    t_token_type type;
    char *value;
    struct s_token *next;
    struct s_token *prev;
} t_token;

typedef struct s_ast
{
    t_node_type type;
    char **args;
    char *filename;
    struct s_ast *left;
    struct s_ast *right;
} t_ast;


t_token *get_token(char *input);
const char *token_type_to_string(t_token_type type);
t_ast *parse(t_token **token);
void print_ast(t_ast *node);
void free_ast(t_ast *node);
void free_tokens(t_token *token);

#endif