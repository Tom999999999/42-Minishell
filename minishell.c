/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tecker <tecker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:54:07 by dolifero          #+#    #+#             */
/*   Updated: 2024/06/11 13:27:57 by tecker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	leaks(void)
{
	system("leaks minishell");
}

int	main(void)
{
	t_ast	*ast;
	t_token	*token;
	t_token	*tmp;
	char *input;
	char *prompt;

	// atexit(leaks);
	while (1)
	{
		prompt = get_prompt();
		input = readline(prompt);
		add_history(input);
		token = get_token(input);
		tmp = token;
		ast = parse(&token);
		ast->ms.token = tmp;
		ast->ms.input = input;
		ast->ms.prompt = prompt;
		print_token(tmp); 
		printf("\n\n");
		print_ast(ast);
		evaluate_ast(ast);
		write(1, "aaaa\n", 5);
		free_ms(ast);
	}
}
