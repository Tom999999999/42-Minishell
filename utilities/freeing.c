/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tecker <tecker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:08:26 by dolifero          #+#    #+#             */
/*   Updated: 2024/06/11 13:22:37 by tecker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_ms(t_ast *ast)
{
	free(ast->ms.input);
	free(ast->ms.prompt);
	free_tokens(ast->ms.token);
	// free_ast(ast);
}
