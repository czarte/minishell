/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 14:14:58 by smelicha          #+#    #+#             */
/*   Updated: 2024/08/06 18:37:35 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

/**
 * Gives back position of the last slah in the given string
 */
int	last_slash(const char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == '/')
			j = i;
		str++;
		i++;
	}
	return (j);
}

/**
 * Modified version of strjoin for joining string with path, automatically
 * adds a slash
 */
char	*ft_join_path(const char *str1, const char *str2)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	ret = NULL;
	ret = malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2) + 2));
	if (!ret)
		return (NULL);
	while (str1[i])
		ret[j++] = str1[i++];
	i = 0;
	ret[j++] = '/';
	while (str2[i])
		ret[j++] = str2[i++];
	ret[j] = '\0';
	return (ret);
}

char	*ft_join_path_v(char const *s1, char const *s2)
{
	int		len;
	char	*s1_2;
	int		i;

	if ((!s1 || !s2) || (!s1 && !s2))
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2);
	s1_2 = (char *)malloc(len * sizeof(char) + 1);
	i = 0;
	if (!s1_2)
		return (0);
	while (*s1)
	{
		s1_2[i] = *s1;
		s1++;
		i++;
	}
	while (*s2)
	{
		s1_2[i] = *s2;
		s2++;
		i++;
	}
	s1_2[i] = '\0';
	return (s1_2);
}

bool	remove_check_char(char c, char *chars)
{
	int	char_i;

	char_i = 0;
	while (chars[char_i])
	{
		if (c == chars[char_i])
			return (true);
		char_i++;
	}
	return (false);
}

void	remove_chars(char *str, char *chars)
{
	int	str_i;
	int	cpy_i;

	if (!str)
		return ;
	str_i = 0;
	cpy_i = 0;
	while (str[str_i])
	{
		if (!remove_check_char(str[str_i], chars))
			str[cpy_i++] = str[str_i];
		str_i++;
	}
	str[cpy_i] = '\0';
}
