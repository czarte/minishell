/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: voparkan <voparkan@student.42prague.cz>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:07:28 by voparkan          #+#    #+#             */
/*   Updated: 2024/07/21 20:32:59 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"
#include "../../incl/executor.h"

void	ft_exec_child(t_executor *pt, t_list *com, int pi[2])
{
	int		exit_code;
	char 	**argv;

	argv = (char **) com->content;
	if (com->prev && dup2(pt->fd_m, STDIN_FILENO) < 0)
		perror("unable bind file descriptor fd_m\n");
	if (close(pi[0]) < 0)
		perror("unable to close fd-0\n");
	if (com->next && dup2(pi[1], STDOUT_FILENO) < 0)
		perror("unable bind file descriptor fd[1]\n");
	if (close(pi[1]) < 0)
		perror("unable to close fd-1\n");
	if (com->prev)
		close(pt->fd_m);
	exit_code = execve(argv[0], &argv[1], pt->env);
	exit(exit_code);
}

void	ft_exec(t_executor *pt, int pi[2], int n)
{
	pt->pid[n] = fork();
	pid = pt->pid[n];
	if (pt->pid[n] == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pt->pid[n] == 0)
		ft_exec_child(pt, pt->comm, pi);
}
