/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: voparkan <voparkan@student.42prague.cz>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:09:55 by voparkan          #+#    #+#             */
/*   Updated: 2024/07/19 10:51:00 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"
#include "../../incl/executor.h"

int	init_path(t_executor *pt)
{
	char		**pth;
	int			i;

	i = 0;
	while (pt->env[i] != NULL)
	{
		if (!strncmp(pt->env[i], "PATH", 4))
		{
			pth = ft_split(pt->env[i], '=');
			pt->path = ft_split(pth[1], ':');
		}
		if (!strncmp(pt->env[i], "PWD", 3))
		{
			pth = ft_split(pt->env[i], '=');
			pt->pwd = pth[1];
		}
		if (!strncmp(pt->env[i], "HOME", 3))
		{
			pth = ft_split(pt->env[i], '=');
			pt->home = pth[1];
		}
		i++;
	}
	if (!(*pt->pwd || *pt->path))
		return (0);
	return (1);
}

char	*open_infile(t_executor *pt, char *filename)
{
	if (ft_strncmp(filename, "/", 1))
		return ft_strjoin(pt->pwd, ft_strjoin("/", filename));
	else
		return filename;
}

int	init_file(t_executor *pt)
{
	char	*file1;
	char	*file2;
	char	*mes;
	char	*ermess;

	ermess = "pipex: permission denied: ";
	file1 = open_infile(pt, pt->argv[1]);
	pt->filefd[0] = open(file1, O_RDONLY);
	file2 = ft_strjoin(pt->pwd, ft_strjoin("/", pt->argv[pt->argc - 1]));
	pt->filefd[1] = open(file2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if ((pt->filefd[0] == -1) || (pt->filefd[1] == -1))
	{
		if (pt->filefd[0] == -1)
			mes = ft_strjoin(ermess, pt->argv[1]);
		else
			mes = ft_strjoin(ermess, pt->argv[pt->argc - 1]);
		printf("%s\n", mes);
		free(mes);
		if (pt->filefd[1] == -1)
			exit (127);
	}
	dup2(pt->filefd[0], STDIN_FILENO);
	close(pt->filefd[0]);
	return (1);
}

t_executor	ft_init_exec(int argc, char **argv, char **env)
{
	t_executor	pt;

	(void)argv;
	pt.comm = malloc(sizeof(t_list));
	pt.comm = NULL;
	pt.end = 0;
	pt.status = 0;
	pt.env = env;
	pt.pwd = NULL;
	pt.path = NULL;
	pt.argc = argc;
//	pt.psucc = init_path(&pt);
	pt.file[0] = malloc(sizeof (char *));
	pt.file[1] = malloc(sizeof (char *));
	return (pt);
}

void	ft_loop(t_executor *pt)
{
	if (pt->file[0])
		pt->fsucc = init_in_file(pt);
	if (pt->file[1])
		pt->fsucc = init_out_file(pt);
	while (!pt->end)
	{
		if (!pt->end)
			if (pt->comm->next == NULL)
				pt->end = 1;
		ft_exec(pt);
		close(pt->fd[1]);
		if (pt->comm->prev)
			close(pt->fd_m);
		pt->comm = pt->comm->next;
	}
}
