/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:51:19 by stepan            #+#    #+#             */
/*   Updated: 2024/09/02 19:00:36 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

/**
 * Builtin echo command function, work in progress
 */

int	ft_isprint(int c)
{
	return (c >= 32 && c <= 126);
}

void	echo(char **echo_tok)
{
	char	**current;
	char	new_line;

	current = &echo_tok[2];
	new_line = 1;
	if (current && str_comp(*current, "-n"))
	{
		new_line = 0;
		current++;
	}
	if (!*current)
		return ;
	while (*current)
	{
		write(STDOUT_FILENO, *current, ft_strlen(*current));
		current++;
		if (*current)
			write(STDOUT_FILENO, " ", 1);
	}
	if (new_line)
		write(STDOUT_FILENO, "\n", 1);
	g_last_status = 0;
}
