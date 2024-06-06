/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tecker <tecker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:54:07 by dolifero          #+#    #+#             */
/*   Updated: 2024/06/06 17:33:02 by tecker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void leaks(void)
{
	system("leaks minishell");
}

int main(void)
{
	char *input;
	char *prompt;

	// atexit(leaks);
	while (1)
	{
		prompt = get_prompt();
		input = readline(prompt);

		t_token *token = get_token(input);
		t_token *tmp = token;
		t_token *tmp2 = token;
		t_ast *ast = parse(&token);

		print_token(tmp);
		printf("\n\n");
		print_ast(ast);

		free_tokens(tmp2);
		free_ast(ast);

		ft_execute(input);
		free(prompt);
	}
}
