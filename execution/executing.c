/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:09:27 by dolifero          #+#    #+#             */
/*   Updated: 2024/06/11 00:50:13 by tomecker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	command_nest(t_ast *ast)
{
	int	builtin;

	builtin = command_is_builtin(ast->args);
	if (builtin)
		ft_execute_builtin(ast, builtin);
	else
		execvp(ast->args[0], ast->args);
		// ft_printf("I didn't make it yet\n");
}

void redirect(t_ast *ast)
{
	int fd;
	int res;

	if (ast->type == N_LESS)
	{
		fd = open(ast->filename, O_RDONLY);
		// if (fd < 0)
		// 	ft_error();
		res = dup2(fd, STDIN_FILENO);
		// if (res < 0)
		// 	ft_error();
	}
	else
	{
		fd = open(ast->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		// if (fd < 0)
		// 	ft_error();
		res = dup2(fd, STDOUT_FILENO);
		// if (res < 0)
		// 	ft_error(); 
	}
	close (fd);
}

void pipe_execution(t_ast *ast)
{
	int pipefd[2];
	pid_t pid1;
	pid_t pid2;

	pipe(pipefd);
	pid1 = fork();
	if (pid1 == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		evaluate_ast(ast->left);
		exit(0);
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		evaluate_ast(ast->right);
		exit(0);
	}
	close (pipefd[0]);
	close (pipefd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

void and_or_execution(t_ast *ast)
{
	int status;
	pid_t pid1;
	pid_t pid2;

	pid1 = fork();
	if (pid1 == 0)
	{
		evaluate_ast(ast->left);
		exit(0);
	}
	else
	{
		waitpid(pid1, &status, 0);
		if ((status == 0 && ast->type == N_AND) || (status != 0 && ast->type == N_OR))
		{
			pid2 = fork();
			if (pid2 == 0)
			{
				evaluate_ast(ast->right);
				exit(0);	
			}
			else
				waitpid(pid2, NULL, 0);
		}
	}
}

void	evaluate_ast(t_ast *ast)
{
	int std_in;
	int std_out;
	
	if (ast->type == N_LESS || ast->type == N_GREAT)
	{
		std_in = dup(STDIN_FILENO);
		std_out = dup(STDOUT_FILENO);
		redirect(ast);
		evaluate_ast(ast->left);
		dup2(std_in, STDIN_FILENO);
		dup2(std_out, STDOUT_FILENO);
		close(std_in);
		close(std_out);
	}
	if (ast->type == N_DGREAT || ast->type == N_DLESS)
		ft_printf("nothing yet\n");
	if (ast->type == N_PIPE)
		pipe_execution(ast);
	if (ast->type == N_AND || ast->type == N_OR)
		and_or_execution(ast);
	if (ast->type == N_COMMAND)
		command_nest(ast);
}
