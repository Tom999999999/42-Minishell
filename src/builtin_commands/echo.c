/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:53:39 by dolifero          #+#    #+#             */
/*   Updated: 2024/06/11 17:29:33 by tomecker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_echo(char **arguments)
{
	if (strcmp(arguments[1], "-n") == 0)
		ft_printf("%s", arguments[2]);
	else
		ft_printf("%s\n", arguments[1]);
}
