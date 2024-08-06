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
char	*ft_strjoin(const char *str1, const char *str2)
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

char	*ft_strjoin_v(char const *s1, char const *s2)
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

/**
 * Count how many characters does the string contain
 */
int	ft_contains_char(const char *str, char character)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == character)
			res++;
		i++;
	}
	return (res);
}
