/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: voparkan <voparkan@student.42prague.cz>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:14:41 by voparkan          #+#    #+#             */
/*   Updated: 2024/08/05 19:41:30 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"
#include "../../incl/executor.h"

void	ft_lstclear(t_list **lst, void (*del)(void**, t_executor*), \
	t_executor *pt)
{
	t_list	*nxt;

	if (!*lst)
		return ;
	while (*lst)
	{
		nxt = (*lst)->next;
		ft_lstdelone(*lst, del, pt);
		*lst = nxt;
	}
	*lst = NULL;
}

void	ft_lstdelone(t_list *lst, void (*del)(void**, t_executor*), \
	t_executor *pt)
{
	(*del)(lst->content, pt);
	free(lst);
}

void	ft_lstadd_back(t_list **lst, t_list *nlist)
{
	if (!*lst)
	{
		nlist->prev = NULL;
		*lst = nlist;
	}
	else
	{
		nlist->prev = ft_lstlast(*lst);
		ft_lstlast(*lst)->next = nlist;
	}
}

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*curr;

	if (!lst)
		return (lst);
	curr = lst;
	while (curr->next != NULL)
		curr = curr->next;
	return (curr);
}

t_list	*ft_lstnew(void *content)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (list)
	{
		list->content = content;
		list->next = NULL;
	}
	return (list);
}
