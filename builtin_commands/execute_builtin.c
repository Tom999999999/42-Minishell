/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolifero <dolifero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:59:59 by dolifero          #+#    #+#             */
/*   Updated: 2024/06/10 18:44:44 by dolifero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_execute_builtin(t_shell *ms, int builtin)
{
	if (builtin == EXIT)
		ft_exit(ms);
	else if (builtin == CD)
		ch_dir(ms->ast->args[1]);
	else if (builtin == PWD)
		ft_pwd();
	else if (builtin == ECHO)
		ft_echo(ms->ast->args);
	// else if (strcmp(arguments[0], "exit") == 0)
	// else if (strcmp(arguments[0], "exit") == 0)
	// else if (strcmp(arguments[0], "exit") == 0)
	// else if (strcmp(arguments[0], "exit") == 0)
	// else if (strcmp(arguments[0], "exit") == 0)
}
