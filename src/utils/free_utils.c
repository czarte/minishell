/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:13:17 by voparkan          #+#    #+#             */
/*   Updated: 2024/08/05 19:42:16 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"
#include "../../incl/executor.h"

void	ft_free_content(char **content, t_executor *pt)
{
	int	i;

	i = 0;
	while ((char *)(content)[i] != NULL)
	{
		if (pt->deubg)
			printf("free: %s\n", (char *) content[i]);
		free(content[i]);
		i++;
	}
}

int	check_path_and_files(t_executor *pt)
{
	return (pt->fsucc && pt->psucc);
}

void	exit_error(t_executor *pt, int exitcode)
{
	if (pt->pid != 0)
	{
		waitpid(-1, &pt->status, WNOHANG);
		pt->status = exitcode;
		free_alloc(pt);
		exit (pt->status);
	}
}

void	free_alloc(t_executor *pt)
{
	if (pt->deubg)
		check_commands(pt);
	if (pt->infile)
		free(pt->infile);
	if (pt->outfile)
		free(pt->outfile);
	ft_lstclear(&pt->comm, (void *)(ft_free_content), pt);
	pt->comm = NULL;
}
