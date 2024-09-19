/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 17:05:30 by smelicha          #+#    #+#             */
/*   Updated: 2024/08/06 18:07:52 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static void	dsts(char *dest, const char *src, size_t l)
{
	size_t	i;

	i = 0;
	while (l > 0)
	{
		dest[i] = src[i];
		l--;
		i++;
	}
}

static void	sstd(char *dest, const char *src, size_t l)
{
	size_t	i;

	i = l - 1;
	while (l > 0)
	{
		dest[i] = src[i];
		l--;
		i--;
	}
}

void	*ft_memmove(void *dest, const void *src, size_t l)
{
	if (dest == src)
		return (dest);
	if (dest < src)
	{
		dsts((char *)dest, (const char *)src, l);
		return (dest);
	}
	if (dest > src)
	{
		sstd((char *)dest, (const char *)src, l);
		return (dest);
	}
	return (NULL);
}
