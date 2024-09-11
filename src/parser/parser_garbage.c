/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:19:31 by smelicha          #+#    #+#             */
/*   Updated: 2024/07/22 13:46:17 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	print_garbage_list(t_executor *pt)
{
	t_garbage	*tmp;

	tmp = pt->garbage;
	while (tmp)
	{
		if (pt->debug)
			printf("link: %p address: %p\n", tmp, tmp->addr);
		tmp = tmp->next;
	}
}

int	new_garbage_list(void *ptr, t_executor *pt)
{
	pt->garbage = malloc(sizeof(t_garbage));
	if (!pt->garbage)
		return (-1);
	pt->garbage->addr = ptr;
	pt->garbage->next = NULL;
	return (0);
}



void	*add_to_collection(void *ptr, t_executor *pt)
{
	t_garbage	*tmp;

	if (!pt->garbage)
	{
		if (new_garbage_list(ptr, pt) < 0)
			return (NULL);
		return (ptr);
	}
	tmp = pt->garbage;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = malloc(sizeof(t_garbage));
	if (!tmp->next)
		return (NULL);
	tmp->next->addr = ptr;
	tmp->next->next = NULL;
	return (ptr);
}

void	**add_array_to_collection(void **ptr, t_executor *pt)
{
	void	**tmp;

	tmp = ptr;
	if (!add_to_collection((void *)tmp, pt))
		return (NULL);
	while (*tmp)
	{
		if (!add_to_collection(*tmp, pt))
			return (NULL);
		tmp++;
	}
	return (ptr);
}

void	clean_garbage(t_executor *pt)
{
	t_garbage	*tmp;
	t_garbage	*next;

	print_garbage_list(pt);
	if (!pt->garbage)
		return;
	next = pt->garbage;
	while (next)
	{
		tmp = next;
		next = tmp->next;
		free(tmp->addr);
		// printf("free: %p\n", tmp);
		free(tmp);
	}
}
