/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolifero <dolifero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:10:37 by dolifero          #+#    #+#             */
/*   Updated: 2024/06/10 18:40:55 by dolifero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	command_is_builtin(char **args)
{
	if (strcmp(args[0], "echo") == 0)
		return (ECHO);
	else if (strcmp(args[0], "cd") == 0)
		return (CD);
	else if (strcmp(args[0], "pwd") == 0)
		return (PWD);
	else if (strcmp(args[0], "export") == 0)
		return (EXPORT);
	else if (strcmp(args[0], "unset") == 0)
		return (UNSET);
	else if (strcmp(args[0], "env") == 0)
		return (ENV);
	else if (strcmp(args[0], "exit") == 0)
		return (EXIT);
	else
		return (NONE);
}
