#include "test.h"

t_ast *expr(int prec, t_token **token);


t_ast *create_ast_node(t_node_type type)
{
    t_ast *node = (t_ast *)malloc(sizeof(t_ast));
	if(node)
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
		return(2);
	if	(type == T_AND || type == T_OR)
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
			node->type = N_COMMAND;
			t_token *curr_token = *token;
			int arg_count = 0;
			while (curr_token && curr_token->type == T_IDENTIFIER)
			{
				arg_count++;
				curr_token = curr_token->next;
			}
			node->args = malloc(sizeof(char *) * (arg_count + 1));
			curr_token = *token;
			while(i < arg_count)
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

t_ast *led(t_ast *left, t_token **token)
{
    t_ast *node = NULL;
    int prec = get_precedence((*token)->type);

    if (prec > 0)
    {
        if (prec == 1)
        {
            // If precedence is 1, create a N_PIPE node
            node = create_ast_node(N_PIPE);
            if (!node)
                exit(1);
        }
        else if (prec == 2)
        {
            // If precedence is 2, create a N_GREAT node
            node = create_ast_node(N_GREAT);
            if (!node)
                exit(1);

            // Ensure that the left child is a N_PIPE node
            if (left->type != N_PIPE)
            {
                fprintf(stderr, "Invalid left child for N_GREAT node");
                exit(1);
            }

            node->left = left;
            *token = (*token)->next;

            if ((*token)->type == T_IDENTIFIER)
            {
                node->filename = (*token)->value;
                (*token) = (*token)->next;
            }
            else
            {
                fprintf(stderr, "Missing filename after redirection operator");
                exit(1);
            }
        }
    }
    else
    {
        fprintf(stderr, "Invalid token precedence");
        exit(1);
    }

    // Recursively parse the right-hand side of the expression
    node->right = expr(prec, token);
    return node;
}


t_ast *expr(int prec, t_token **token)
{
	int i = 0;
	t_ast *left = nud(token);
	while (*token && get_precedence((*token)->type) > prec)
	{
		left = led(left, token);
	}
	return (left);
}

t_ast *parse(t_token **token)
{
	t_ast *node = NULL;
	node = expr(0, token);
	return (node);
}
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

void print_ast(t_ast *node) {
    if (!node) return;

    printf("Node Type: %s\n", node_type_to_string(node->type));

    if (node->args) {
        printf("Arguments:\n");
        for (int i = 0; node->args[i]; i++) {
            printf("%s ", node->args[i]);
        }
        printf("\n");
    }

    if (node->filename) {
        printf("Filename: %s\n", node->filename);
    }

    printf("\n");

    print_ast(node->left);
    print_ast(node->right);
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

