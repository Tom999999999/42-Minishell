#include "../includes/minishell.h"
t_ast *expr(int prec, t_token **token);


t_ast *create_ast_node(t_node_type type)
{
    t_ast *node = (t_ast *)malloc(sizeof(t_ast));
	if(node)
	{
		node->type = type;
		node->args = NULL;
		node->filename = NULL;
		node->heredoc = NULL;
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
	if (type == T_GREAT || type == T_LESS || type == T_DGREAT || type == T_DLESS)
		return(2);
	if	(type == T_AND || type == T_OR)
		return (3);
	if (type == T_OPAR || type == T_CPAR)
        return (4);
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
			while (i < arg_count)
			{
				node->args[i] = strdup(curr_token->value);
				curr_token = curr_token->next;
				i++;
			}
			node->args[arg_count] = NULL;
			*token = curr_token;
		}
		else if ((*token)->type == T_OPAR)
		{
			(*token) = (*token)->next;
			node = expr(3, token);
			if ((*token) && (*token)->type == T_CPAR)
				(*token) = (*token)->next;
			else
			{
				printf("parenthesis do not close\n");
				exit(1);
			}
		}
	}
	return (node);
}

void create_note(t_token_type type, t_ast **node)
{
	if (type == T_PIPE)
		*node = create_ast_node(N_PIPE);
	else if (type == T_GREAT)
		*node = create_ast_node(N_GREAT);
	else if (type == T_LESS)
		*node = create_ast_node(N_LESS);
	else if (type == T_AND)
		*node = create_ast_node(N_AND);
	else if (type == T_OR)
		*node = create_ast_node(N_OR);
}

t_ast *led(t_ast *left, t_token **token)
{
	t_ast *node = NULL;
	int prec = get_precedence((*token)->type);

	if (prec > 0)
	{
		create_note((*token)->type, &node);
		node->left = left;
		*token = (*token)->next;

		if(prec == 2)
		{
			if ((*token)->type == T_IDENTIFIER)
			{
				node->filename = strdup((*token)->value);
				(*token) = (*token)->next;
			}
			else
			{
				printf("missing file after redirection operator");
				exit(1);
			}
		}
		else
            node->right = expr(prec, token);
	}
	return (node);
}

t_ast *expr(int prec, t_token **token)
{
	t_ast *left = nud(token);
	while (*token && get_precedence((*token)->type) <= prec)
	{
		if ((*token)->type == T_CPAR)
			break;
		left = led(left, token);
	}
	return (left);
}

t_ast *parse(t_token **token)
{
	t_ast *node = NULL;
	node = expr(3, token);
	return (node);
}
