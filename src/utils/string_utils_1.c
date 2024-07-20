/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 14:14:58 by smelicha          #+#    #+#             */
/*   Updated: 2024/07/20 14:15:56 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

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
