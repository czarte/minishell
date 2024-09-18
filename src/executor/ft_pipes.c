/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:09:55 by voparkan          #+#    #+#             */
/*   Updated: 2024/09/12 18:58:49 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"
#include "../../incl/executor.h"

char	*open_infile(t_executor *pt, char *filename)
{
	char	*tmp;
	char	*path;

	tmp = NULL;
	path = NULL;
	if (pt->debug)
	{
		printf("pt->pwd: %s\n", pt->pwd);
		printf("filename: %s\n", filename);
	}
	if (ft_strncmp(filename, "/", 1))
	{
		tmp = ft_join_path("/", filename);
		add_to_collection((void *)tmp, pt);
		path = ft_join_path(pt->pwd, tmp);
		add_to_collection((void *)path, pt);
		return (path);
	}
	else
		return (filename);
}

int	count_pipes(t_executor *pt)
{
	t_list	*execs;
	int		i;

	i = 0;
	execs = pt->comm;
	while (execs)
	{
		i++;
		execs = execs->next;
	}
	if (pt->debug)
		printf("number of pipes: %i\n", i);
	return (i);
}

t_executor	*ft_init_exec(t_data *data)
{
	t_executor	*pt;

	pt = malloc(sizeof(t_executor));
	if (pt < 0)
		perror("unable to allocate t_exec");
	pt->debug = data->debug;
	pt->fork = false;
	pt->c_pi = 0;
	pt->pid = NULL;
	pt->parsing_ok = false;
	pt->comm = NULL;
	pt->garbage = NULL;
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
	pt->data = data;
	data->parse_fail = false;
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

	n = 0;
	cmi = 0;
	if (pt->debug)
	{
		printf("infile %s\n", pt->infile);
		printf("outfile %s\n", pt->outfile);
	}
	if (pt->outfile != NULL)
		pt->fsucc = init_out_file(pt, pi);
	exec_loop(pt, fd_m, pi, &cmi);
	while (n < cmi)
	{
		if (pt->fork)
			g_last_status = wait_subprocess(pt, n);
		n++;
		g_pid = 0;
	}
	return (g_last_status);
}
