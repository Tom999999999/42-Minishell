/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolifero <dolifero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:12:28 by dolifero          #+#    #+#             */
/*   Updated: 2024/06/10 15:36:17 by dolifero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ch_dir(char *path)
{
	if (!path)
	{
		if (getenv("HOME") == NULL)
			return ((void)ft_printf("HOME is not set\n"));
		return (ch_dir(getenv("HOME")));
	}
	if (chdir(path) == -1)
		ft_printf("%s: %s\n", strerror(errno), path);
}
