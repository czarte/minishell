/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_cmd_trim.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 17:05:30 by smelicha          #+#    #+#             */
/*   Updated: 2024/08/06 18:07:52 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"
#include "../../incl/executor.h"

bool	only_char(char *str, char c)
{
	if (!str)
		return (true);
	while (*str)
	{
		if (*str != c)
			return (false);
		str++;
	}
	return (true);
}

typedef struct s_ctrim_data {
	int		i;
	int		last_space_pos;
	char	*src;
	bool	first_letter;
}	t_ctrim_data;

void	cmd_trim_cont(t_ctrim_data *td, char *cmd, char c)
{
	while (cmd[td->i])
	{
		if (!td->first_letter && (cmd[td->i] != c))
		{
			td->src = (cmd + td->i);
			td->first_letter = true;
		}
		if (td->i)
		{
			if (cmd[td->i] == c && cmd[td->i - 1] != c)
				td->last_space_pos = td->i;
		}
		td->i++;
	}
}

void	cmd_trim(char *cmd, char c)
{
	t_ctrim_data	td;

	if (only_char(cmd, c))
		return ;
	td.i = 0;
	td.last_space_pos = 0;
	td.first_letter = false;
	td.src = NULL;
	if (!cmd || !*cmd)
		return ;
	cmd_trim_cont(&td, cmd, c);
	if (cmd[td.i - 1] == c)
		cmd[td.last_space_pos] = '\0';
	ft_memmove(cmd, td.src, (ft_strlen(td.src) + 1));
}
