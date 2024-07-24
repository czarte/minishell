/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: voparkan <voparkan@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by voparkan          #+#    #+#             */
/*   Updated: 2024/07/18 11:01:16 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../incl/minishell.h"
# include "../../incl/executor.h"

int	init_in_file(t_executor *pt)
{
	char	*file1;
	char	*mes;
	char	*ermess;

	ermess = "pipex: permission denied: ";
	file1 = open_infile(pt, pt->file[0]);
	pt->filefd[0] = open(file1, O_RDONLY);
	if (pt->filefd[0] == -1)
	{
		mes = ft_strjoin(ermess, pt->file[0]);
		printf("%s\n", mes);
		free(mes);
	}
	dup2(pt->filefd[0], STDIN_FILENO);
	close(pt->filefd[0]);
	return (1);
}

int	init_out_file(t_executor *pt)
{
	char	*file2;
	char	*mes;
	char	*ermess;

	ermess = "pipex: permission denied: ";
	mes = ft_strjoin(ermess, pt->file[1]);
	printf("%s\n", mes);
	file2 = ft_strjoin(pt->pwd, ft_strjoin("/", pt->file[1]));
	pt->filefd[1] = open(file2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pt->filefd[1] == -1)
	{
		mes = ft_strjoin(ermess, pt->file[1]);
		printf("%s\n", mes);
		exit (127);
	}
	return (1);
}
