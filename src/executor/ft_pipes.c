/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:09:55 by voparkan          #+#    #+#             */
/*   Updated: 2024/08/06 16:40:20 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"
#include "../../incl/executor.h"

char	*open_infile(t_executor *pt, char *filename)
{
	if (pt->deubg)
	{
		printf("pt->pwd: %s\n", pt->pwd);
		printf("filename: %s\n", filename);
	}
	if (ft_strncmp(filename, "/", 1))
		return (ft_join_path(pt->pwd, ft_join_path("/", filename)));
	else
		return (filename);
}

int	count_pipes(t_data *data)
{
	t_list	*execs;
	int		i;

	i = 0;
	execs = data->exec->cmd;
	while (execs)
	{
		i++;
		execs = execs->next;
	}
	return (i);
}

t_executor	*ft_init_exec(t_data *data)
{
	t_executor	*pt;
	int			i;

	i = 0;
	pt = malloc(sizeof(t_executor));
	if (pt < 0)
		perror("unable to allocate t_exec");
	pt->c_pi = count_pipes(data) + 1;
	if (pt->c_pi > 0)
	{
		pt->pid = (int *)malloc((pt->c_pi + 1) * sizeof(int));
		while (i < pt->c_pi)
		{
			pt->pid[i] = -1;
			i++;
		}
	}
	else
		pt->pid = NULL;
	pt->deubg = false;
	pt->deubg = false;
	pt->parsing_ok = false;
	pt->comm = NULL;
	pt->heredoc = false;
	pt->heredoc_rl = false;
	pt->append = false;
	pt->end = 0;
	pt->status = 0;
	pt->env = data->envp;
	pt->home = NULL;
	pt->pwd = NULL;
	pt->path = NULL;
	pt->argv = NULL;
	pt->infile = NULL;
	pt->outfile = NULL;
	pt->dlmtr = NULL;
	pt->filefd[0] = 0;
	pt->filefd[1] = 0;
	return (pt);
}

bool	exec_loop(t_executor *pt, int fd_m, int pi[2], int *cmi)
{
	while (!pt->end)
	{
		if (pipe(pi) == -1)
		{
			perror("pipe");
		}
		if (!pt->end)
			if (pt->comm->next == NULL)
				pt->end = 1;
		ft_exec(pt, pi, fd_m);
		close(pi[1]);
		if (pt->comm->prev)
			close(fd_m);
		fd_m = check_heredoc(pt, pi);
		if (pt->comm->next)
			pt->comm = pt->comm->next;
		else
		{
			if (pt->outfile)
				dup2(0, 1);
			(*cmi)++;
			break ;
		}
	}
	return (false);
}

int	ft_loop(t_executor *pt, int fd_m)
{
	int		pi[2];
	int		cmi;
	int		n;
	int		exit_code;

	n = 0;
	cmi = 0;
	if (pt->deubg)
	{
		printf("infile %s\n", pt->infile);
		printf("outfile %s\n", pt->outfile);
	}
	if (pt->outfile != NULL)
		pt->fsucc = init_out_file(pt, pi);
	exec_loop(pt, fd_m, pi, &cmi);
	while (n < cmi)
	{
		exit_code = wait_subprocess(pt, n++);
		g_pid = 0;
	}
	return (exit_code);
}
