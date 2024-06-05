#include <stdio.h>
#include <stdlib.h>

typedef enum {
    T_IDENTIFIER,
    T_PIPE,
    T_GREAT,
    T_LESS,
    T_AND,
    T_OR
} t_token_type;

typedef enum {
    N_COMMAND,
    N_PIPE,
    N_GREAT,
    N_LESS,
    N_AND,
    N_OR
} t_node_type;

typedef struct s_token {
    t_token_type type;
    char *value;
    struct s_token *next;
} t_token;

typedef struct s_ast {
    t_node_type type;
    char **args;
    char *filename;
    struct s_ast *left;
    struct s_ast *right;
} t_ast;

t_ast *create_ast_node(t_node_type type)
{
    t_ast *node = (t_ast *)malloc(sizeof(t_ast));
    if (node)
    {
        node->type = type;
        node->args = NULL;
        node->filename = NULL;
        node->left = NULL;
        node->right = NULL;
    }
    return (node);
}

int get_precedence(t_token_type type)
{
    if (type == T_IDENTIFIER)
        return (0);
    if (type == T_PIPE)
        return (1);
    if (type == T_GREAT || type == T_LESS)
        return (2);
    if (type == T_AND || type == T_OR)
        return (3);
    printf("error precedence");
    return (-1);
}

t_ast *nud(t_token **token)
{
    int i = 0;
    t_ast *node = NULL;
    if (*token)
    {
        if ((*token)->type == T_IDENTIFIER)
        {
            node = create_ast_node(N_COMMAND);
            if (!node)
                exit(1);
            t_token *curr_token = *token;
            int arg_count = 0;
            while (curr_token && curr_token->type == T_IDENTIFIER)
            {
                arg_count++;
                curr_token = curr_token->next;
            }
            node->args = malloc(sizeof(char *) * (arg_count + 1));
            curr_token = *token;
            while (i < arg_count)
            {
                node->args[i] = curr_token->value;
                curr_token = curr_token->next;
                i++;
            }
            node->args[arg_count] = NULL;
            *token = curr_token;
        }
    }
    return (node);
}

t_ast *expr(int prec, t_token **token);

t_ast *led(t_ast *left, t_token **token)
{
    t_ast *node = NULL;
    int current_prec = get_precedence((*token)->type);

    // Create the node based on the current token
    if ((*token)->type == T_PIPE)
        node = create_ast_node(N_PIPE);
    else if ((*token)->type == T_GREAT)
        node = create_ast_node(N_GREAT);
    else if ((*token)->type == T_LESS)
        node = create_ast_node(N_LESS);
    else
    {
        printf("unexpected token");
        exit(1);
    }

    node->left = left;
    *token = (*token)->next;

    if (node->type == N_GREAT || node->type == N_LESS)
    {
        if ((*token)->type == T_IDENTIFIER)
        {
            node->filename = (*token)->value;
            *token = (*token)->next;
        }
        else
        {
            printf("missing file after redirection operator");
            exit(1);
        }
    }
    else
    {
        node->right = expr(current_prec, token);
    }

    return (node);
}

t_ast *expr(int prec, t_token **token)
{
    t_ast *left = nud(token);
    while (*token && get_precedence((*token)->type) > prec)
    {
        left = led(left, token);
    }
    return (left);
}

t_ast *parse(t_token **token)
{
    return expr(0, token);
}

void print_ast(t_ast *node, int level)
{
    if (node == NULL)
        return;

    for (int i = 0; i < level; i++)
        printf("  ");

    switch (node->type)
    {
    case N_COMMAND:
        printf("Node Type: N_COMMAND\n");
        if (node->args)
        {
            for (int i = 0; node->args[i] != NULL; i++)
            {
                for (int j = 0; j < level + 1; j++)
                    printf("  ");
                printf("Argument: %s\n", node->args[i]);
            }
        }
        break;
    case N_PIPE:
        printf("Node Type: N_PIPE\n");
        break;
    case N_GREAT:
        printf("Node Type: N_GREAT\n");
        for (int i = 0; i < level + 1; i++)
            printf("  ");
        printf("Filename: %s\n", node->filename);
        break;
    case N_LESS:
        printf("Node Type: N_LESS\n");
        for (int i = 0; i < level + 1; i++)
            printf("  ");
        printf("Filename: %s\n", node->filename);
        break;
    case N_AND:
        printf("Node Type: N_AND\n");
        break;
    case N_OR:
        printf("Node Type: N_OR\n");
        break;
    }

    print_ast(node->left, level + 1);
    print_ast(node->right, level + 1);
}

// Test the code
int main()
{
    // Create tokens for "cat test.txt | grep \"baum hallo\" > output.txt"
    t_token token1 = {T_IDENTIFIER, "cat", NULL};
    t_token token2 = {T_IDENTIFIER, "test.txt", NULL};
    t_token token3 = {T_PIPE, "|", NULL};
    t_token token4 = {T_IDENTIFIER, "grep", NULL};
    t_token token5 = {T_IDENTIFIER, "baum hallo", NULL};
    t_token token6 = {T_GREAT, ">", NULL};
    t_token token7 = {T_IDENTIFIER, "output.txt", NULL};

    // Link the tokens
    token1.next = &token2;
    token2.next = &token3;
    token3.next = &token4;
    token4.next = &token5;
    token5.next = &token6;
    token6.next = &token7;

    // Parse the tokens
    t_token *token_list = &token1;
    t_ast *ast = parse(&token_list);

    // Print the AST
    print_ast(ast, 0);

    return 0;
}
