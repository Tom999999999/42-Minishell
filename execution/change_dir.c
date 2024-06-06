/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolifero <dolifero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:12:28 by dolifero          #+#    #+#             */
/*   Updated: 2024/06/05 17:25:55 by dolifero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ch_dir(char *input)
{
	char	*path;

	path = trim_dir_path(input);
	if (!path)
		return ;
	if (chdir(path) == -1)
		ft_printf("%s: %s\n", strerror(errno), path);
}
