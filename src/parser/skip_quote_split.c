/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 22:10:07 by smelicha          #+#    #+#             */
/*   Updated: 2024/09/17 21:17:14 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"
#include "../../incl/executor.h"

size_t	ft_skip_quote_count_tokens(char const *s, char c);
size_t	ft_skip_quote_token_len(char const *s, char c);
int	ft_skip_quote_create_tokens(char **result, char const *s, char c);

char	**ft_skip_quote_split(char const *s, char c)
{
	size_t	num_words;
	char	**result;

	num_words = ft_skip_quote_count_tokens(s, c);
	result = malloc((num_words + 1) * sizeof(result));
	if (!result)
		return (free(result), NULL);
	if (ft_skip_quote_create_tokens(result, s, c) != 3)
		result[num_words] = NULL;
	else
		return (result = NULL);
	return (result);
}

size_t	ft_skip_quote_count_tokens(char const *s, char c)
{
	size_t	count;
	int		in_word;
	char	quote;
	char	*last_char;

	count = 0;
	last_char = (char *)s + ft_strlen(s);
	quote = '\0';
	in_word = 0;
	while (*s && s < last_char)
	{
		if (*s == '\'' || *s == '\"')
		{
			quote = *s;
			s++;
			while (*s && *s != quote)
				s++;
			quote = '\0';
		}
		if (*s == c)
			in_word = 0;
		else if (in_word == 0)
		{
			in_word = 1;
			count++;
		}
		if (s < last_char)
			s++;
	}
	return (count);
}

size_t	ft_skip_quote_token_len(char const *s, char c)
{
	size_t	len;
	char	quote;

	quote = '\0';
	len = 0;
	while (*s && *s != c)
	{
		if (*s == '\"' || *s == '\'')
		{
			if (!quote)
				quote = *s;
			s++;
			len++;
			while (*s && *s != quote)
			{
				len++;
				s++;
			}
			quote = '\0';
		}
		if (*s)
		{
			len++;
			s++;
		}
	}
	return (len);
}

int	ft_skip_quote_create_tokens(char **result, char const *s, char c)
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
			len = ft_skip_quote_token_len(s, c);
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

char	*ft_skip_quote_strrchr(const char *s, int c)
{
	int		sl;
	int		i;
	char	*res;
	char	quote;

	sl = ft_strlen(s);
	i = sl;
	quote = '\0';
	res = NULL;
	if ((char) c == '\0')
		return ((char *)(s + sl));
	while (i > 0)
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			quote = s[i];
			i--;
			while ((s[i] && s[i] != quote) && i > 0)
				i--;
			quote = '\0';
		}
		if (s[i] == (char) c)
			break ;
		i--;
	}
	if (i < 0)
		return (NULL);
	if (s[i] == (char) c)
		res = ((char *) s + i);
	return ((char *)res);
}
