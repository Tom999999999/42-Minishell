/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolifero <dolifero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:09:27 by dolifero          #+#    #+#             */
/*   Updated: 2024/06/10 18:47:44 by dolifero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	command_nest(t_shell *ms)
{
	int	builtin;

	builtin = command_is_builtin(ms->ast->args);
	if (builtin)
		ft_execute_builtin(ms, builtin);
	else
		ft_printf("I didn't make it yet\n");
}

void	evaluate_ast(t_shell *ms)
{
	if (ms->ast->type == N_COMMAND)
		command_nest(ms);
}
