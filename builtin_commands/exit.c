/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolifero <dolifero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:38:22 by dolifero          #+#    #+#             */
/*   Updated: 2024/06/10 17:19:34 by dolifero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exit(t_shell *ms)
{
	int	exit_code;

	exit_code = 0;
	if (ms->ast->args[1] != NULL)
	{
		if (ms->ast->args[2] != NULL && !atoi(ms->ast->args[1]))
			return ((void)ft_putendl_fd("exit: too many arguments",
					STDERR_FILENO));
		else if (!atoi(ms->ast->args[1]))
			exit_code = 255;
		else
			exit_code = atoi(ms->ast->args[1]);
		free_ms(ms);
		exit(exit_code);
	}
	else
	{
		free_ms(ms);
		exit(exit_code);
	}
}
