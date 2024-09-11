/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_counter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: voparkan <voparkan@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by voparkan          #+#    #+#             */
/*   Updated: 2024/08/05 21:06:21 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	count_number_of_tokens(char **cmd, int *n, char *quote)
{
	while (*cmd && **cmd)
	{
		while (**cmd && **cmd == ' ')
			(*cmd)++;
		if (**cmd == '\"' || **cmd == '\'')
		{
			*quote = **cmd;
			(*cmd)++;
			while (**cmd && **cmd != *quote)
				(*cmd)++;
			(*cmd)++;
		}
		else
		{
			while (**cmd && **cmd != ' ' && !(**cmd == '\"' || **cmd == '\''))
				(*cmd)++;
		}
		(*n)++;
	}
}

/**
 * Counts how many tokens are in the command
 */
int	number_of_tokens(char *cmd)
{
	int		n;
	char	quote;

	n = no_space_tokens(cmd);
	quote = '\0';
	count_number_of_tokens(&cmd, &n, &quote);
	return (n);
}

int	check_for_no_space_token(char *cmd)
{
	int		i;
	char	quote;

	i = 0;
	quote = '\0';
	while (cmd[i])
	{
		if (cmd[i] == '\'' || cmd [i] == '\"')
		{
			quote = cmd[i];
			i++;
			while (cmd[i] && cmd[i] != quote)
				i++;
		}
		if (cmd[i] == ' ')
			return (0);
		if (cmd[i] == '|' || cmd[i] == '<' || cmd[i] == '>')
			return (i);
		i++;
	}
	return (0);
}
