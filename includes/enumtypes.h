/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enumtypes.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolifero <dolifero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:03:20 by dolifero          #+#    #+#             */
/*   Updated: 2024/06/10 18:38:15 by dolifero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUMTYPES_H
# define ENUMTYPES_H

# include "minishell.h"

typedef enum s_token_type
{
	T_IDENTIFIER,
	T_PIPE,
	T_GREAT,
	T_LESS,
	T_DLESS,
	T_DGREAT,
	T_AND,
	T_OR,
	T_OPAR,
	T_CPAR
}				t_token_type;

typedef enum s_node_type
{
	N_COMMAND,
	N_PIPE,
	N_GREAT,
	N_LESS,
	N_DLESS,
	N_DGREAT,
	N_AND,
	N_OR
}				t_node_type;

typedef enum s_builtin_type
{
	NONE,
	EXIT,
	PWD,
	CD,
	ENV,
	EXPORT,
	UNSET,
	ECHO
}				t_builtin_type;

#endif
