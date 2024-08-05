/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: voparkan <voparkan@student.42prague.cz>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:09:55 by voparkan          #+#    #+#             */
/*   Updated: 2024/08/04 17:56:25 by voparkan         ###   ########.fr       */
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
	printf("pt->pwd: %s\n", pt->pwd);
	printf("filename: %s\n", filename);
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
	if (dup2(pt->filefd[0], STDIN_FILENO) < 0)
		perror("problem dupliacte file fd");
	close(pt->filefd[0]);
	return (1);
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

t_executor	ft_init_exec(int argc, char **argv, t_data *data)
{
	t_executor	*pt;

	(void)argv;
	pt = malloc(sizeof(t_executor));
	if (pt < 0)
		perror("unable to allocate t_exec");
	pt->c_pi = count_pipes(data) + 1;
	pt->pid = (int *)malloc((pt->c_pi + 1) * sizeof(int));
	pt->comm = NULL;
	pt->heredoc = false;
	pt->heredoc_rl = false;
	pt->append = false;
	pt->end = 0;
	pt->status = 0;
	pt->env = data->envp;
	pt->pwd = NULL;
	pt->path = NULL;
	pt->argc = argc;
	pt->infile = NULL;
	pt->outfile = NULL;
	pt->dlmtr = NULL;
	pt->filefd[0] = 0;
	pt->filefd[1] = 0;
	return (*pt);
}

int check_heredoc(t_executor *pt, int pi[2])
{
	int fd_m;

	if (pt->filefd[0])
	{
		close(pi[0]);
		printf("pt->filefd[0]: %d\n", pt->filefd[0]);
		fd_m = pt->filefd[0];
	} else
		fd_m = pi[0];
	return (fd_m);
}

int	ft_loop(t_executor *pt, int fd_m)
{
	int		pi[2];
	int		cmi;
	int		n;
	int		exit_code;

	n = 0;
	cmi = 0;
	printf("infile %s\n", pt->infile);
	printf("outfile %s\n", pt->outfile);
	if (pt->outfile != NULL)
		pt->fsucc = init_out_file(pt, pi);
	while (!pt->end)
	{
		if (pipe(pi) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
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
			cmi++;
			break;
		}
	}
	while (n < cmi)
		exit_code = wait_subprocess(pt, n++);
	return (exit_code);
}
