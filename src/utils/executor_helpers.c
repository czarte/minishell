/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: voparkan <voparkan@student.42prague.cz>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:10:53 by voparkan          #+#    #+#             */
/*   Updated: 2024/07/02 16:11:07 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"
#include "../../incl/executor.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*c;
	unsigned char	*d;

	c = (unsigned char *) s1;
	d = (unsigned char *) s2;
	while (n--)
		if (*c++ != *d++ || (!*(c - 1) || !*(d - 1)))
			return (*(c - 1) - *(d - 1));
	return (0);
}