/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:13:17 by voparkan          #+#    #+#             */
/*   Updated: 2024/08/06 17:22:21 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"
#include "../../incl/executor.h"

void	ft_free_content(char **content, t_executor *pt)
{
	content = NULL;
	content = content + 1;
	pt->debug = pt->debug;
}

void	free_alloc(t_executor *pt)
{
	if (pt->comm)
		while (pt->comm->prev)
			pt->comm = pt->comm->prev;
	ft_lstclear(&pt->comm, (void *)(ft_free_content), pt);
	free(pt->comm);
	free(pt->pid);
	pt->comm = NULL;
}

void	free_old_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
	{
		free(envp[i]);
		envp[i] = NULL;
		i++;
	}
	free(envp);
}
