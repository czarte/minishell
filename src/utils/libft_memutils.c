/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_memutils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: voparkan <voparkan@student.42prague.cz>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 12:22:35 by voparkan          #+#    #+#             */
/*   Updated: 2024/06/30 12:23:10 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	*ft_memcpy_o(void *dst, const void *src, size_t n)
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