/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stepan <stepan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:51:54 by stepan            #+#    #+#             */
/*   Updated: 2024/04/17 17:52:40 by stepan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

/**
 * Copies string to preallocated memory from from to to
 */
void	str_fill(char *to, char *from)
{
	int	i;

	i = 0;
	while (from[i])
	{
		to[i] = from[i];
		i++;
	}
}

/**
 * Compares two strings and returns the length of the strings if they are same
 * or 0 if they differ from each other
 */
int	str_comp(const char *str1, const char *str2)
{
	int	i;

	i = 0;
	if (!str1 || !str2)
		return (0);
	while (str1[i] && str2[i])
	{
		if (str1[i] == str2[i])
			i++;
		else
			return (0);
	}
	if (str1[i] || str2[i])
		return (0);
	return (i);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_memcpy(const char *str)
{
	char	*cpy;
	int		i;

	cpy = NULL;
	i = 0;
	if (!str)
		return (NULL);
	cpy = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!cpy)
		return (NULL);
	while (str[i])
	{
		cpy[i] = str[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

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
	{
		ret[j] = str1[i];
		i++;
		j++;
	}
	i = 0;
	ret[j] = '/';
	j++;
	while (str2[i])
	{
		ret[j] = str2[i];
		i++;
		j++;
	}
	ret[j] = '\0';
	// printf("ret: %s\n", ret);
	return (ret);
}
