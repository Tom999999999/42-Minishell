/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:08:26 by dolifero          #+#    #+#             */
/*   Updated: 2024/06/11 22:44:51 by tomecker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_all(t_ast *ast)
{
	free(ast->ms.input);
	free(ast->ms.prompt);
	free_tokens(ast->ms.token);
	free_ast(ast);
}
