/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: voparkan <voparkan@student.42prague.cz>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:07:28 by voparkan          #+#    #+#             */
/*   Updated: 2024/07/22 19:05:38 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"
#include "../../incl/executor.h"

void	ft_exec_child(t_executor *pt, t_list *com, int pi[2], int fd_m)
{
	char 	**argv;

	argv = (char **) com->content;
	if (com->prev && dup2(fd_m, STDIN_FILENO) < 0)
		perror("unable to dup fd_m\n");
	close(pi[0]);
	if (com->next && dup2(pi[1], STDOUT_FILENO) < 0)
		perror("unable to dup pi[1]\n");
	close(pi[1]);
	if (com->prev)
		close(fd_m);
	execve(argv[0], &argv[1], pt->env);

}

int	ft_exec(t_executor *pt, int pi[2], int fd_m)
{
	static int	i;

	if (pt->end)
	{
		i = 0;
		pt->end = 0;
	}
	pt->pid[i] = fork();
	pid = pt->pid[i];
	if (pt->pid[i] == -1)
	{
		perror("fork error");
		exit(EXIT_FAILURE);
	}
	if (pt->pid[i] == 0)
		ft_exec_child(pt, pt->comm, pi, fd_m);
	i++;
	return (EXIT_SUCCESS);
}

// if (com->prev && com->next == NULL && close(pi[0]) < 0)
// 	perror("com-next unable to close fd-0\n");
// if (com->prev && com->next == NULL && dup2(pi[1], STDIN_FILENO) < 0)
// 	perror("com->prev unable bind file descriptor fd_m\n");
// if (com->prev && com->next == NULL && (close(pi[1]) < 0))
// 	perror("com-next unable to close fd-1\n");
// if (com->prev && com->next && dup2(pi[1], STDIN_FILENO) < 0)
// 	perror("com->prev unable bind file descriptor fd_m\n");
// if (com->prev && com->next && close(pi[1]) < 0)
// 	perror("com-next unable to close fd-1\n");
// if (com->prev && com->next && dup2(pi[0], STDOUT_FILENO) < 0)
// 	perror("com->prev unable bind file descriptor fd_m\n");
// if (com->prev && com->next && close(pi[0]) < 0)
// 	perror("com-next unable to close fd-1\n");
// if (com->next && com->prev == NULL && close(pi[1]) < 0)
// 	perror("com-next unable to close fd-1\n");
// if (com->next && com->prev == NULL && dup2(pi[0], STDOUT_FILENO) < 0)
// 	perror("com-next unable bind file descriptor fd[1]\n");
// if (com->next && com->prev == NULL && close(pi[0]) < 0)
// 	perror("com-next unable to close fd-0\n");
