/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 12:14:34 by voparkan          #+#    #+#             */
/*   Updated: 2024/09/15 19:51:06 by voparkan         ###   ########.fr       */
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

static void	*ft_rcpy(char *dst, const char *src, size_t n);

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

static void	*ft_rcpy(char *dst, const char *src, size_t n)
{
	size_t	i;

	i = n - 1;
//	printf("len: %zu\n", i);
	while (n > 0)
	{
//		printf("dest: %s\n", (dst + i));
//		printf("src: %s\n", (src + i));
		*(dst + i) = *(src + i);
		i--;
		n--;
	}
	return (dst);
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

char	**ft_split(char const *s, char c)
{
	size_t	num_words;
	char	**result;

	num_words = ft_count_tokens(s, c);
	result = malloc((num_words + 1) * sizeof(result));
	if (!result)
		return (free(result), NULL);
	if (ft_create_tokens(result, s, c) != 3)
		result[num_words] = NULL;
	else
		return (result = NULL);
	return (result);
}

size_t	ft_count_tokens(char const *s, char c)
{
	size_t	count;
	int		in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s == c)
			in_word = 0;
		else if (in_word == 0)
		{
			in_word = 1;
			count++;
		}
		s++;
	}
	return (count);
}

size_t	ft_token_len(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (*s && *s != c)
	{
		len++;
		s++;
	}
	return (len);
}

int	ft_create_tokens(char **result, char const *s, char c)
{
	int	i;
	int	len;

	i = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			len = ft_token_len(s, c);
			result[i] = malloc((len + 1));
			if (!result[i])
			{
				while (i-- > 0)
					free(result[i]);
				return (free(result), 3);
			}
			ft_memcpy(result[i], s, len);
			result[i][len] = '\0';
			s += len;
			i++;
		}
	}
	return (0);
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

int	ft_lstsize(t_list *lst)
{
	int	i;

	if (!lst)
		return (0);
	i = 0;
	while (lst->next != NULL)
	{
		lst = lst->next;
		i++;
	}
	i++;
	return (i);
}
