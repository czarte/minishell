/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 17:05:30 by smelicha          #+#    #+#             */
/*   Updated: 2024/08/06 18:07:52 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static void	*ft_rcpy(char *dst, const char *src, size_t n)
{
	size_t	i;

	i = n - 1;
	while (n > 0)
	{
		*(dst + i) = *(src + i);
		i--;
		n--;
	}
	return (dst);
}

void	*ft_memmovev(void *dst, const void *src, size_t len)
{
	if (dst == src)
		return (dst);
	else if (dst < src)
		ft_memcpy((char *) dst, (char *) src, len);
	else if (dst > src)
		ft_rcpy((char *) dst, (char *) src, len);
	return (dst);
}

char	*ft_strrchr(const char *s, int c)
{
	int		sl;
	int		i;
	char	*res;

	sl = ft_strlen(s);
	i = sl;
	res = NULL;
	if ((char) c == '\0')
		return ((char *)(s + sl));
	while (i >= 0)
	{
		if (s[i] == (char) c)
		{
			res = ((char *) s + i);
			break ;
		}
		i--;
	}
	return ((char *)res);
}

size_t	ft_strlcat(char *dest, char *src, size_t size)
{
	size_t	i;
	size_t	slen;
	size_t	dlen;

	i = 0;
	dlen = (size_t)ft_strlen(dest);
	slen = (size_t)ft_strlen(src);
	if (dlen >= size)
		return (size + slen);
	while (((size - 1) > (i + dlen)) && src[i] != '\0')
	{
		dest[i + dlen] = src[i];
		i++;
	}
	dest[i + dlen] = '\0';
	return (dlen + slen);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	size_t	ml;
	size_t	s1len;

	s1len = ft_strlen(s1);
	if (!s1 || !s2)
		return (NULL);
	ml = s1len + ft_strlen(s2);
	p = malloc((ml + 1) * sizeof (char));
	if (!p)
		return (NULL);
	ft_memcpy(p, (const void *) s1, s1len);
	ft_memcpy(p + s1len, (const void *) s2, ml - s1len);
	p[ml] = '\0';
	return (p);
}
