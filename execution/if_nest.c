/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_nest.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:59:59 by dolifero          #+#    #+#             */
/*   Updated: 2024/06/10 16:45:53 by tomecker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>


void redirection(t_ast *node)
{
    int fd;

    if (node->type == N_LESS)
	{
        fd = open(node->filename, O_RDONLY);
        if (fd < 0)
		{
            perror("open");
            exit(1);
        }
        if (dup2(fd, STDIN_FILENO) < 0)
		{
            perror("dup2");
            close(fd);
            exit(1);
        }
        close(fd);
    }
	else if (node->type == N_GREAT)
	{
        fd = open(node->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd < 0)
		{
            perror("open");
            exit(1);
        }
        if (dup2(fd, STDOUT_FILENO) < 0)
		{
            perror("dup2");
            close(fd);
            exit(1);
        }
        close(fd);
    }
}

void execute_command(t_ast *node)
{
    if (execvp(node->args[0], node->args) < 0)
	{
        perror("execvp");
        exit(1);
    }
}

void ft_execute(t_ast *node)
{
    int status;
    int saved_stdin = dup(STDIN_FILENO);
    int saved_stdout = dup(STDOUT_FILENO);

    if (node->type == N_LESS || node->type == N_GREAT)
	{
        redirection(node);
        ft_execute(node->left);
        dup2(saved_stdin, STDIN_FILENO);
        dup2(saved_stdout, STDOUT_FILENO);
        close(saved_stdin);
        close(saved_stdout);
    }
	else if (node->type == N_PIPE)
	{
        int pipefd[2];
        pid_t pid1, pid2;

        if (pipe(pipefd) < 0)
		{
            perror("pipe");
            exit(1);
        }

        if ((pid1 = fork()) < 0) 
		{
            perror("fork");
            exit(1);
        }

        if (pid1 == 0)
		{
            close(pipefd[0]);
            dup2(pipefd[1], STDOUT_FILENO);
            close(pipefd[1]);
            ft_execute(node->left);
            exit(0);
        }

        if ((pid2 = fork()) < 0)
		{
            perror("fork");
            exit(1);
        }

        if (pid2 == 0)
		{
            close(pipefd[1]);
            dup2(pipefd[0], STDIN_FILENO);
            close(pipefd[0]);
            ft_execute(node->right);
            exit(0);
        }

        close(pipefd[0]);
        close(pipefd[1]);

        waitpid(pid1, &status, 0);
        waitpid(pid2, &status, 0);
    }
	else if (node->type == N_COMMAND)
	{
		pid_t pid = fork();
		if (pid < 0)
		{
			perror("fork");
			exit(1);
		}
		else if (pid == 0)
		{
			execute_command(node);
			exit(0);
		}
		else
		{
			waitpid(pid, &status, 0);
		}
	}
    else
        fprintf(stderr, "Error: command not found\n");
}