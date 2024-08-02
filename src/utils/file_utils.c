/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: voparkan <voparkan@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by voparkan          #+#    #+#             */
/*   Updated: 2024/08/02 13:02:29 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../incl/minishell.h"
# include "../../incl/executor.h"

int	init_in_file(t_executor *pt)
{
	char	*file1;
	char	*mes;
	char	*ermess;

	ermess = "minishell: input permission denied: ";
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

int	init_out_file(t_executor *pt)
{
	char	*file2;
	char	*mes;
	char	*ermess;

	ermess = "minishell: output file permission denied: ";
	mes = ft_strjoin(ermess, pt->outfile);
	printf("%s\n", mes);
	file2 = ft_strjoin(pt->pwd, ft_strjoin("/", pt->outfile));
	pt->filefd[1] = open(file2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pt->filefd[1] == -1)
	{
		mes = ft_strjoin(ermess, pt->outfile);
		printf("%s\n", mes);
		exit (127);
	}
	return (1);
}
