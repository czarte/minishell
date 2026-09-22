/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_memutils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 12:22:35 by voparkan          #+#    #+#             */
/*   Updated: 2024/07/20 14:22:55 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char			*dest;
	const char		*source;
	unsigned int	i;

	dest = dst;
	source = src;
	i = 0;
	if (dest == 0 && source == 0)
		return (0);
	while (n > 0)
	{
		dest[i] = source[i];
		i++;
		n--;
	}
	return (dst);
}
