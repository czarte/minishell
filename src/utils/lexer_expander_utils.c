/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 22:10:07 by smelicha          #+#    #+#             */
/*   Updated: 2024/09/01 18:55:59 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"
#include "../../incl/executor.h"

bool	is_var_char(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9') || c == '_' || c == '?')
		return (true);
	return (false);
}

char	*fill_res(char *res, char *str)
{
	while (*str)
	{
		*res = *str;
		res++;
		str++;
	}
	return (res);
}

void	split_main_string(char *main, char *main1, char *main2, int d_p)
{
	int	i;

	i = 0;
	while (i != d_p)
	{
		main1[i] = *main;
		main++;
		i++;
	}
	main1[i] = '\0';
	main++;
	i = 0;
	while (is_var_char(*main))
		main++;
	while (*main)
	{
		main2[i] = *main;
		main++;
		i++;
	}
	main2[i] = '\0';
}

char	*get_var_name(int d_p, t_lex_cmd *lc)
{
	char	*tmp;
	char	*var_name;
	int		i;

	var_name = NULL;
	i = 0;
	tmp = (lc->cmd + d_p + 1);
	while (*tmp != ' ' && *tmp != '\0')
	{
		tmp++;
		i++;
	}
	var_name = malloc(sizeof(char) * (i + 1));
	tmp = (lc->cmd + d_p + 1);
	i = 0;
	while (is_var_char(*tmp))
	{
		var_name[i] = *tmp;
		tmp++;
		i++;
	}
	var_name[i] = '\0';
	return (var_name);
}

int	ft_expandable(char *cmd)
{
	int	j;

	j = 0;
	while (*cmd)
	{
		if (*cmd == '\'')
		{
			cmd++;
			j++;
			while (*cmd && *cmd != '\'')
			{
				cmd++;
				j++;
			}
		}
		if (*cmd == '$')
			return (j);
		if (*cmd)
		{
			cmd++;
			j++;
		}
	}
	return (-1);
}
