/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:13:17 by voparkan          #+#    #+#             */
/*   Updated: 2024/07/21 19:43:26 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"
#include "../../incl/executor.h"

void	ft_free_content(char *content)
{
	if (content)
		free(content);
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
	if (pt->comm)
		ft_lstclear(&pt->comm, (void *)(ft_free_content));
}
