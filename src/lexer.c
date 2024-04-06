/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 22:10:07 by smelicha          #+#    #+#             */
/*   Updated: 2024/04/06 23:09:00 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	number_of_tokens(char *cmd)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (cmd[i])
	{
		while (cmd[i] && cmd[i] == ' ')
			i++;
		if (cmd[i])
			n++;
		while (cmd[i] && cmd[i] != ' ')
			i++;
	}
	return (n);
}

int	allocate_cmd_chain(char *cmd, t_data *data)
{
	int			i;
	t_cmd_chain	*prev;
	t_cmd_chain	*current;

	i = number_of_tokens(cmd);
	current = NULL;
	prev = data->cmd_chain;
	while (i)
	{
		current = malloc(sizeof(t_cmd_chain));
		if (!current)
		{
			perror("cmd_chain: ");
			return (-1);
		}
		current->next = NULL;
		current->cmd = NULL;
		prev->next = current;
		prev = current;
		current = NULL;
		i--;
	}
	return (0);
}

int	lexer(char *cmd, t_data *data)
{
	data = data;

	printf("cmd from lexer: %s\n", cmd);
	printf("number of tokens: %i\n", number_of_tokens(cmd));
	return (0);
}
