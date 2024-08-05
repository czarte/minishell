/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by voparkan          #+#    #+#             */
/*   Updated: 2024/08/05 16:53:15 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../incl/minishell.h"
# include "../../incl/executor.h"

int	init_in_file(t_executor *pt)
{
	char	*file1;
	char	*mes;
	char	*ermess;

	pt->heredoc = false;
	ermess = "minishell: input file permission denied: ";
	file1 = open_infile(pt, pt->infile);
	printf("file1: %s\n", file1);
	pt->filefd[0] = open(file1, O_RDONLY);
	printf("infile fd: %d\n", pt->filefd[0]);
	if (pt->filefd[0] == -1)
	{
		mes = ft_strjoin(ermess, pt->infile);
		printf("%s\n", mes);
		free(mes);
	}
	dup2(pt->filefd[0], STDIN_FILENO);
	// close(pt->filefd[0]);
	return (1);
}

int	init_out_file(t_executor *pt, int pi[2])
{
	char	*mes;
	char	*ermess;

	ermess = "minishell: output file permission denied: ";
	printf("outfile: %s\n", pt->outfile);
	printf("append: %d\n", pt->append);
	if (pt->append)
		pt->filefd[1] = open(pt->outfile, O_CREAT | O_RDWR | O_APPEND, 0644);
	else
		pt->filefd[1] = open(pt->outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pt->filefd[1] == -1)
	{
		mes = ft_strjoin(ermess, pt->outfile);
		printf("%s\n", mes);
		exit (127);
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
		mes = ft_strjoin_v(ermess, file);
		printf("%s\n", mes);
		exit(127);
	}
	return (fd);
}
