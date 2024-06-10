#include "../includes/minishell.h"

t_token	*ft_new_token(char *value, t_token_type type)
{
	t_token	*new_token;

	new_token = (t_token *)calloc(1, sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = strdup(value);
	new_token->type = type;
	return (new_token);
}

void	ft_token_list_add_back(t_token **lst, t_token *new_token)
{
	t_token	*curr_node;

	if (!*lst)
	{
		*lst = new_token;
		return ;
	}
	curr_node = *lst;
	while (curr_node && curr_node->next)
		curr_node = curr_node->next;
	curr_node->next = new_token;
	new_token->prev = curr_node;
}

int	add_token(t_token **lst, t_token_type type, char *input, int i)
{
	t_token	*new;
	char	*value;
	int		count;

	count = i;
	if (type == T_OPAR || type == T_CPAR)
	{
		count++;
	}
	else if (input[i] == '\'' || input[i] == '\"')
	{
		count++;
		while (input[count] && input[count] != '\'' && input[count] != '\"')
			count++;
		count++;
	}
	else
	{
		while (input[count] && !isspace(input[count]))
			count++;
	}
	value = (char *)calloc((count - i) + 1, sizeof(char));
	if (!value)
		exit(1);
	strncpy(value, input + i, count - i);
	value[count - i] = '\0';
	new = ft_new_token(value, type);
	ft_token_list_add_back(lst, new);
	free(value);
	return (count);
}

t_token	*get_token(char *input)
{
	t_token	*lst;
	int		i;

	lst = NULL;
	i = 0;
	while (input[i])
	{
		while (isspace(input[i]))
			i++;
		if (input[i] == '|' && input[i + 1] != '|')
			i = add_token(&lst, T_PIPE, input, i);
		else if (input[i] == '>' && input[i + 1] == '>')
			i = add_token(&lst, T_DGREAT, input, i);
		else if (input[i] == '>')
			i = add_token(&lst, T_GREAT, input, i);
		else if (input[i] == '<' && input[i + 1] == '<')
			i = add_token(&lst, T_DLESS, input, i);
		else if (input[i] == '<')
			i = add_token(&lst, T_LESS, input, i);
		else if (input[i] == '|' && input[i + 1] == '|')
			i = add_token(&lst, T_OR, input, i);
		else if (input[i] == '&' && input[i + 1] == '&')
			i = add_token(&lst, T_AND, input, i);
		else if (input[i] == '(')
			i = add_token(&lst, T_OPAR, input, i);
		else if (input[i] == ')')
			i = add_token(&lst, T_CPAR, input, i);
		else if (input[i])
			i = add_token(&lst, T_IDENTIFIER, input, i);
	}
	return (lst);
}
