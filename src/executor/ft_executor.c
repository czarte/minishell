/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: voparkan <voparkan@student.42prague.cz>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:07:28 by voparkan          #+#    #+#             */
/*   Updated: 2024/07/19 10:48:44 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"
#include "../../incl/executor.h"

void	ft_exec_child(t_executor *pt, t_list *com)
{
	int		res;
	char 	**argv;

	argv = (char **) com->content;
	if (com->prev)
	{
		printf("com->prev\n");
		dup2(pt->fd_m, STDIN_FILENO);
	}
	close(pt->fd[0]);
	if (com->next)
	{
		printf("com->next");
		dup2(pt->fd[1], STDOUT_FILENO);
	}
	close(pt->fd[1]);
	if (com->prev)
		close(pt->fd_m);
	res = execve(argv[0], &argv[1], pt->env);
	if (res == -1)
		exit (127);
}

//void	ft_exec_parent(t_executor *pt)
//{
//	if (pt->end)
//	{
//		if (pt->file[1]) {
//			dup2(pt->filefd[1], STDOUT_FILENO);
//			close(pt->filefd[1]);
//		}
//		else {
//			close(pt->fd[0]);
//			close(pt->fd[1]);
//		}
//	}
//	else
//	{
//		dup2(pt->fd[0], STDIN_FILENO);
//		close(pt->fd[0]);
//		close(pt->fd[1]);
//	}
//}

void	ft_exec(t_executor *pt)
{
	if (pipe(pt->fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pt->pid = fork();
	pid = pt->pid;
	if (pt->pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pt->pid == 0)
		ft_exec_child(pt, pt->comm);
//	else
//		ft_exec_parent(pt);
}
