/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolifero <dolifero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:08:37 by dolifero          #+#    #+#             */
/*   Updated: 2024/06/10 17:12:22 by dolifero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "minishell.h"

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct s_ast
{
	t_node_type		type;
	char			**args;
	char			*filename;
	char			*heredoc;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

typedef struct s_shell
{
	char			*input;
	char			*prompt;
	t_ast			*ast;
}					t_shell;

#endif
