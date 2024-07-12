/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: voparkan <voparkan@student.42prague.cz>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:07:28 by voparkan          #+#    #+#             */
/*   Updated: 2024/07/10 20:18:26 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"
#include "../../incl/executor.h"

void	ft_exec_child(t_executor *pt, char **argv)
{
	int		res;

	if (pt->end)
	{
		if (pt->file[1]) {
			dup2(pt->filefd[1], STDOUT_FILENO);
			close(pt->filefd[1]);
		} else {
			dup2(pt->fd[1], STDOUT_FILENO);
			close(pt->fd[1]);
			close(pt->fd[0]);
		}
		res = execve(argv[0], &argv[1], pt->env);
		if (res == -1)
			exit (127);
	}
	else
	{
		dup2(pt->fd[1], STDOUT_FILENO);
		close(pt->fd[1]);
		close(pt->fd[0]);
		res = execve(argv[0], &argv[1], pt->env);
		if (res == -1)
			exit (127);
	}
}

void	ft_exec_parent(t_executor *pt)
{
	if (pt->end)
	{
		if (pt->file[1]) {
			dup2(pt->filefd[1], STDOUT_FILENO);
			close(pt->filefd[1]);
		}
		else {
			close(pt->fd[0]);
			close(pt->fd[1]);
		}
	}
	else
	{
		dup2(pt->fd[0], STDIN_FILENO);
		close(pt->fd[0]);
		close(pt->fd[1]);
	}
}

void	ft_exec(t_executor *pt, char **argv)
{
	if (pipe(pt->fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pt->pid = fork();
	if (pt->pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pt->pid == 0)
		ft_exec_child(pt, argv);
	else
		ft_exec_parent(pt);
}