#include "test.h"

const char *node_type_to_string(t_node_type type) {
    switch (type) {
        case N_COMMAND:
            return "N_COMMAND";
        case N_LESS:
            return "N_LESS";
        case N_GREAT:
            return "N_GREAT";
        case N_DLESS:
            return "N_DLESS";
        case N_DGREAT:
            return "N_DGREAT";
        case N_PIPE:
            return "N_PIPE";
        case N_AND:
            return "N_AND";
        case N_OR:
            return "N_OR";
        default:
            return "UNKNOWN";
    }
}


void print_ast_helper(t_ast *node, const char *prefix, const char *child_prefix)
{
    if (!node) return;

    printf("%sNode Type: %s\n", prefix, node_type_to_string(node->type));

    if (node->args) {
        printf("%sArguments: ", prefix);
        for (int i = 0; node->args[i]; i++) {
            printf("%s ", node->args[i]);
        }
        printf("\n");
    }

    if (node->filename) {
        printf("%sFilename: %s\n", prefix, node->filename);
    }

    if (node->left) {
        printf("%sLeft:\n", prefix);
        print_ast_helper(node->left, child_prefix, child_prefix);
    }

    if (node->right) {
        printf("%sRight:\n", prefix);
        print_ast_helper(node->right, child_prefix, child_prefix);
    }
}

void print_ast(t_ast *node) {
    print_ast_helper(node, "", "  ");
}

void free_ast(t_ast *node) {
    if (!node) return;

    if (node->type == N_COMMAND) {
        if (node->args) {
            for (int i = 0; node->args[i]; i++) {
                free(node->args[i]);
            }
            free(node->args);
        }
    } else if (node->type == N_GREAT) {
        if (node->filename) {
            free(node->filename);
        }
    }

    free_ast(node->left);
    free_ast(node->right);
    free(node);
}

void free_tokens(t_token *token)
{
    t_token *tmp;
    while (token)
    {
        tmp = token;
        token = token->next;
        free(tmp->value);
        free(tmp);
    }
}
const char *token_type_to_string(t_token_type type)
{
    if (type == T_IDENTIFIER)
        return "T_IDENTIFIER";
    else if (type == T_PIPE)
        return "T_PIPE	";
    else if (type == T_GREAT)
        return "T_GREAT	";
    else if (type == T_LESS)
        return "T_LESS	";
    else if (type == T_DGREAT)
        return "T_DGREAT";
    else if (type == T_DLESS)
        return "T_DLESS		";
    else if (type == T_OR)
        return "T_OR	";
    else if (type == T_AND)
        return "T_AND	";
    else
        return "UNKNOWN";
}