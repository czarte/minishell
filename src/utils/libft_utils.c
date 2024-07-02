/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: voparkan <voparkan@student.42prague.cz>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 12:14:34 by voparkan          #+#    #+#             */
/*   Updated: 2024/06/30 12:14:34 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static int		ft_create_tokens(char **result, char const *s, char c);
static size_t	ft_count_tokens(char const *s, char c);
static size_t	ft_token_len(char const *s, char c);

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

static size_t	ft_count_tokens(char const *s, char c)
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

static size_t	ft_token_len(char const *s, char c)
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

static int	ft_create_tokens(char **result, char const *s, char c)
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
			ft_memcpy_o(result[i], s, len);
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

