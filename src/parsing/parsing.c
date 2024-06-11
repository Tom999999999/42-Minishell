#include "../../includes/minishell.h"

t_ast *expr(int prec, t_token **token);


t_ast *create_ast_node(t_node_type type)
{
    t_ast *node;
	
	node = (t_ast *)malloc(sizeof(t_ast));
	if(node)
	{
		node->type = type;
		node->args = NULL;
		node->filename = NULL;
		node->heredoc = NULL;
		node->left = NULL;
		node->right = NULL;
	}
	else
		error_indicator(1);
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
	error_indicator(1);
	return (-1);
}

t_ast *nud(t_token **token)
{
	int i;
	t_ast *node;
	
	node = NULL;
	i = 0;
	if (*token)
	{
		if ((*token)->type == T_IDENTIFIER)
		{
			node = create_ast_node(N_COMMAND);
			if (!node)
				error_indicator(1);
			node->type = N_COMMAND;
			t_token *curr_token = *token;
			int arg_count = 0;
			while (curr_token && curr_token->type == T_IDENTIFIER)
			{
				arg_count++;
				curr_token = curr_token->next;
			}
			node->args = malloc(sizeof(char *) * (arg_count + 1));
			if (!node->args)
				error_indicator(1);
			curr_token = *token;
			while (i < arg_count)
			{
				node->args[i] = ft_strdup(curr_token->value);
				if (!node->args[i])
					error_indicator(1);
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
				error_indicator(1);;
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
    else if (type == T_DGREAT)
        *node = create_ast_node(N_DGREAT);
    else if (type == T_LESS)
        *node = create_ast_node(N_LESS);
    else if (type == T_DLESS)
        *node = create_ast_node(N_DLESS);
    else if (type == T_AND)
        *node = create_ast_node(N_AND);
    else if (type == T_OR)
        *node = create_ast_node(N_OR);
	if (!node)
		error_indicator(1);
}


t_ast *led(t_ast *left, t_token **token)
{
	t_ast *node;
	int prec;
	
	node = NULL;
	prec = get_precedence((*token)->type);
	if (prec > 0)
	{
		create_note((*token)->type, &node);
		if (!node)
			error_indicator(1);
		node->left = left;
		*token = (*token)->next;

		if ((*token)->prev && (*token)->prev->type == T_DLESS)
		{
			if ((*token)->type == T_IDENTIFIER)
			{
				node->heredoc = ft_strdup((*token)->value);
				if (!node->heredoc)
					error_indicator(1);
				(*token) = (*token)->next;
			}
			else
			{
				printf("missing heredoc delimiter after << operator");
				error_indicator(1);
			}
		}
		else if(prec == 2)
		{
			if ((*token)->type == T_IDENTIFIER)
			{
				node->filename = strdup((*token)->value);
				if (!node->filename)
					error_indicator(1);
				(*token) = (*token)->next;
			}
			else
			{
				printf("missing file after redirection operator");
				error_indicator(1);
			}
			
		}
		else
            node->right = expr(prec, token);
	}
	return (node);
}

t_ast *expr(int prec, t_token **token)
{
	t_ast *left;
	
	left = nud(token);
	while (*token && get_precedence((*token)->type) <= prec)
	{
		if ((*token)->type == T_CPAR)
			break;
		left = led(left, token);
	}
	return (left);
}

t_ast *parse(t_token **token, char *input, char *prompt)
{
	t_ast *node;
	t_token *tmp;
	
	tmp = *token;
	node = NULL;
	node = expr(3, token);
	if (node)
	{
		node->ms.token = tmp;
		node->ms.input = input;
		node->ms.prompt = prompt;
	}
	if (error_indicator(0) > 0)
		ft_error(node, "parsing");
	return (node);
}
