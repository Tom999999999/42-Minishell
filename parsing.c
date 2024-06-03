/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolifero <dolifero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:52:33 by dolifero          #+#    #+#             */
/*   Updated: 2024/06/03 17:26:50 by dolifero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	leaks(void)
{
	system("leaks minishell");
}

int	main(void)
{
	char	*input;

	atexit(leaks);
	while (1)
	{
		input = readline("\033[1;36mminishell > \033[0;39m");
		if (ft_strstr(input, "exit"))
		{
			free(input);
			exit (0);
		}
	}
}
