/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: voparkan <voparkan@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by voparkan          #+#    #+#             */
/*   Updated: 2024/09/12 09:21:21 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"
#include "../../incl/executor.h"

int	init_in_file(t_executor *pt)
{
	char	*file1;
	char	*mes;
	char	*ermess;

	pt->heredoc = false;
	ermess = "minishell: ";
	file1 = open_infile(pt, pt->infile);
	if (pt->debug)
		printf("file1: %s\n", file1);
	pt->filefd[0] = open(file1, O_RDONLY);
	if (pt->debug)
		printf("infile fd: %d\n", pt->filefd[0]);
	if (pt->filefd[0] == -1)
	{
		g_last_status = 1;
		mes = ft_strjoin(ermess, pt->infile);
		perror(mes);
		free(mes);
	}
	dup2(pt->filefd[0], STDIN_FILENO);
	return (1);
}

int	init_out_file(t_executor *pt, int pi[2])
{
	char	*mes;
	char	*ermess;

	ermess = "minishell: output file permission denied: ";
	if (pt->debug)
	{
		printf("outfile: %s\n", pt->outfile);
		printf("append: %d\n", pt->append);
	}
	if (pt->append)
		pt->filefd[1] = open(pt->outfile, O_CREAT | O_RDWR | O_APPEND, 0644);
	else
		pt->filefd[1] = open(pt->outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pt->filefd[1] == -1)
	{
		mes = ft_join_path(ermess, pt->outfile);
		perror(mes);
		free(mes);
		// exit (127);
	}
	pi[1] = pt->filefd[1];
	dup2(pi[1], STDOUT_FILENO);
	close(pt->filefd[1]);
	return (1);
}

int	init_hd_file(char *file, t_executor *pt)
{
	char	*mes;
	char	*ermess;
	int		fd;

	fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	pt->filefd[0] = fd;
	pt->heredoc = true;
	pt->infile = strdup(".tmp_heredoc");
	if (fd == -1)
	{
		ermess = strerror(errno);
		mes = ft_strjoin(ermess, file);
		printf("%s\n", mes);
		exit(127);
	}
	return (fd);
}

int	check_heredoc(t_executor *pt, int pi[2])
{
	int	fd_m;

	if (pt->filefd[0])
	{
		close(pi[0]);
		if (pt->debug)
			printf("pt->filefd[0]: %d\n", pt->filefd[0]);
		fd_m = pt->filefd[0];
	}
	else
		fd_m = pi[0];
	return (fd_m);
}
