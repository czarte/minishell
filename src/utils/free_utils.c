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
	// int	i;
 //
	// i = 0;
	content = NULL;
	content = content + 1;
	pt->debug = pt->debug;
	// while ((char *)(content)[i] != NULL)
	// {
	// 	if (pt->debug)
	// 		printf("free: %s\n", (char *) content[i]);
	// 	free(content[i]);
	// 	i++;
	// }
	// free(content);
}

void	free_alloc(t_executor *pt)
{
	if (pt->comm)
		while (pt->comm->prev)
			pt->comm = pt->comm->prev;
	// if (pt->infile)
	// 	free(pt->infile);
	// if (pt->outfile)
	// 	free(pt->outfile);
	ft_lstclear(&pt->comm, (void *)(ft_free_content), pt);
	free(pt->comm);
	free(pt->pid);
	pt->comm = NULL;
}
