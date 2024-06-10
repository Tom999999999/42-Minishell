/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolifero <dolifero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:54:07 by dolifero          #+#    #+#             */
/*   Updated: 2024/06/10 17:23:13 by dolifero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	leaks(void)
{
	system("leaks minishell");
}

int	main(void)
{
	t_shell	ms;
	t_token	*token;
	t_token	*tmp;
	t_token	*tmp2;

	atexit(leaks);
	while (1)
	{
		ms.prompt = get_prompt();
		ms.input = readline(ms.prompt);
		add_history(ms.input);
		token = get_token(ms.input);
		tmp = token;
		tmp2 = token;
		ms.ast = parse(&token);
		print_token(tmp);
		printf("\n\n");
		print_ast(ms.ast);
		evaluate_ast(&ms);
		free_tokens(tmp2);
		free_ms(&ms);
	}
}
