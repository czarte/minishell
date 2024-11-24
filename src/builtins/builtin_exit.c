/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by voparkan          #+#    #+#             */
/*   Updated: 2024/09/19 13:49:27 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"
#include "../../incl/executor.h"

bool	is_num(char *str)
{
	while (*str)
	{
		if ((*str < '0' || *str > '9') && *str != '-')
			return (false);
		str++;
	}
	return (true);
}

int	count_double_char_strings(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

void	ft_exit_too_many_args(void)
{
	ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	g_last_status = 1;
}

void	ft_exit_not_number(char *str)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	g_last_status = 2;
}

void	ft_exit(char *cmd)
{
	int		i;
	char	**splitted;

	splitted = NULL;
	i = 0;
	if (!cmd)
		return ;
	cmd_trim(cmd, ' ');
	splitted = ft_split(cmd, ' ');
	printf("exit\n");
	remove_chars(splitted[1], "\"\'+");
	if (!is_num(splitted[1]))
		ft_exit_not_number(splitted[1]);
	else if (count_double_char_strings(splitted) > 2)
		ft_exit_too_many_args();
	else if (splitted[1])
		g_last_status = ft_atoi(splitted[1]);
	while (splitted[i])
		free(splitted[i++]);
	free(splitted);
}
