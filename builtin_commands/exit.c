/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tecker <tecker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:38:22 by dolifero          #+#    #+#             */
/*   Updated: 2024/06/11 13:11:20 by tecker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exit(t_ast *ast)
{
	int	exit_code;

	exit_code = 0;
	// if (ast->args[1] != NULL)
	// {
	// 	if (ast->args[2] != NULL && !atoi(ast->args[1]))
	// 		return ((void)ft_putendl_fd("exit: too many arguments",
	// 				STDERR_FILENO));
	// 	else if (!atoi(ast->args[1]))
	// 		exit_code = 255;
	// 	else
	// 		exit_code = atoi(ast->args[1]);
	// 	free_ms(ast);
	// 	exit(exit_code);
	// }
	// else
	// {
		free_ms(ast);
		exit(exit_code);
	// }
}
