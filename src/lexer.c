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

void	print_token_chain(t_data *data)
{
	t_token_chain	*current;

	current = data->token_chain->next;
	while (current)
	{
		printf("token: %s\ttype: %s\n", current->token, current->type);
		current = current->next;
	}
}

int	number_of_tokens(char *cmd)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (cmd[i])
	{
		while (cmd[i] && cmd[i] == ' ')
		{
			if (cmd[i] == '\"' || cmd[i] == '\'')
				n++;
			i++;
		}
		if (cmd[i])
			n++;
		while (cmd[i] && cmd[i] != ' ')
		{
			if (cmd[i] == '\"' || cmd[i] == '\'')
				n++;
			i++;
		}
	}
	return (n);
}

int	token_length(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[i] == '\"' || cmd[i] == '\'')
		return (1);
	while (cmd[i] && cmd[i] != ' ')
		i++;
	return (i);
}

int	fill_token_chain(char *cmd, t_data *data)
{
	t_token_chain	*current;
	char			*token;

	current = data->token_chain->next;
	while (*cmd && *cmd == ' ')
		cmd++;
	while (current)
	{
		current->token = malloc(sizeof(char) * (token_length(cmd) + 1));
		if (current->token == NULL)
		{
			perror("token allocation:");
			return (-1);
		}
		token = current->token;
		if (*cmd == '\"' || *cmd == '\'')
		{
			*token = *cmd;
			token++;
			cmd++;
		}
		while (*cmd && *cmd != ' ' && !(*(cmd - 1) == '\"' || *(cmd - 1) == '\''))
		{
			*token = *cmd;
			token++;
			cmd++;
		}
		*token = '\0';
		while (*cmd && *cmd == ' ')
			cmd++;
		current = current->next;
	}
	return (0);
}

int	allocate_token_chain(char *cmd, t_data *data)
{
	int			i;
	t_token_chain	*prev;
	t_token_chain	*current;

	i = number_of_tokens(cmd);
	current = NULL;
	prev = data->token_chain;
	while (i)
	{
		current = malloc(sizeof(t_token_chain));
		if (!current)
		{
			perror("token_chain: ");
			return (-1);
		}
		current->next = NULL;
		current->token = NULL;
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
	allocate_token_chain(cmd, data);
	fill_token_chain(cmd, data);
	type_token_chain(data);
	print_token_chain(data);
	printf("\n");
	print_token_chain(data);
	free_token_chain(data);
	return (0);
}
