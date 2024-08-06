/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 22:10:07 by smelicha          #+#    #+#             */
/*   Updated: 2024/08/06 13:27:15 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

/**
 * Returns length of token string in command, uses spaces for delimiter
 */
int	token_length(char *cmd)
{
	int		i;
	char	quote;

	i = check_for_no_space_token(cmd);
	quote = '\0';
	if (i)
	{
		return (i);
	}
	if (cmd[i] == '\"' || cmd[i] == '\'')
	{
		quote = cmd[i];
		i++;
		while (cmd[i] != quote)
			i++;
		return (i - 1);
	}
	while (cmd[i] && cmd[i] != ' ')
	{
		if (cmd[i] == '\"' || cmd[i] == '\'')
			break ;
		i++;
	}
	return (i);
}

/**
 * Allocates linked list for all tokens present in command
 */
int	allocate_token_chain(char *cmd, t_data *data)
{
	int				i;
	t_token_chain	*prev;
	t_token_chain	*current;

	i = number_of_tokens(cmd, data);
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

/**
 * Checks for unclosed quotes in command
 * returns 1 if ok
 * returns 0 if ko
 */
int	cmd_quotes_pair_check(char *cmd)
{
	int	dq;
	int	sq;

	dq = 0;
	sq = 0;
	while (cmd && *cmd)
	{
		if (*cmd == '\"')
			dq++;
		else if (*cmd == '\'')
			sq++;
		cmd++;
	}
	if (dq % 2 || sq % 2)
		return (0);
	else
		return (1);
}

void	cmd_space_trim(char *cmd)
{
	int	i;
	int	last_space_pos;

	i = 0;
	last_space_pos = 0;
	if (!cmd || !*cmd)
		return ;
	while (cmd[i])
	{
		if (i)
		{
			if (cmd[i] == ' ' && cmd[i - 1] != ' ')
				last_space_pos = i;
		}
		i++;
	}
	if (cmd[i - 1] == ' ')
		cmd[last_space_pos] = '\0';
}

/**
 * Takes command and processes it resulting in linked list of typed tokens
 * ready for execution
 */
int	lexer(char *cmd, t_data *data)
{
	if (!cmd_quotes_pair_check(cmd))
	{
		printf("Unclosed quotes!\n");
		return (-1);
	}
	cmd_space_trim(cmd);
	exec_data_re_init(data);
	allocate_token_chain(cmd, data);
	fill_token_chain(cmd, data);
	if (type_token_chain(data) < 0)
		return (-1);
	if (data->debug)
		print_token_chain(data);
	token_chain_analyzer(data);
	if (data->debug)
		print_token_chain(data);
	return (0);
}
