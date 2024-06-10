/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolifero <dolifero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:55:24 by dolifero          #+#    #+#             */
/*   Updated: 2024/06/10 18:47:57 by dolifero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "minishell.h"
//MINISHELL PROMPT
char			*get_prompt(void);
char			*trim_dir_path(char *dir_path);
//TOKENISING
t_token			*get_token(char *input);
void			print_token(t_token *token);
void			free_tokens(t_token *token);
//PARSING
t_ast			*parse(t_token **token);
void			print_ast(t_ast *node);
void			free_ast(t_ast *node);
//EXECUTION
void			evaluate_ast(t_shell *ms);
void			command_nest(t_shell *ms);
int				command_is_builtin(char **args);
void			ft_execute_builtin(t_shell *ms, int builtin);
//BUILTIN COMMANDS
void			ch_dir(char *path);
void			ft_pwd(void);
void			ft_echo(char **arguments);
void			ft_exit(t_shell *ms);
//UTILITIES
void			free_ms(t_shell *ms);

#endif
