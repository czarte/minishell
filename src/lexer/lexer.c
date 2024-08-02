/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 22:10:07 by smelicha          #+#    #+#             */
/*   Updated: 2024/08/02 09:11:21 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

/**
 * Debug function
 */
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

/**
 * Counts how many tokens are in the command
 */
int	number_of_tokens(char *cmd)
{
	int		n;
	char	quote;

	n = 0;
	quote = '\0';
	while (cmd && *cmd)
	{
		while (*cmd && *cmd == ' ')
			cmd++;
		if (*cmd == '\"' || *cmd == '\'')
		{
			quote = *cmd;
			cmd++;
			while (*cmd && *cmd != quote)
				cmd++;
			cmd++;
		}
		else
		{
			while (*cmd && *cmd != ' ' && !(*cmd == '\"' || *cmd == '\''))
				cmd++;
		}
		n++;
	}
	return (n);
}

/**
 * Returns length of token string in command, uses spaces for delimiter
 */
int	token_length(char *cmd)
{
	int		i;
	char	quote;

	i = 0;
	quote = '\0';
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

/**
 * Takes command and processes it resulting in linked list of typed tokens
 * ready for execution
 */
int	lexer(char *cmd, t_data *data)
{
	if (!cmd_quotes_pair_check(cmd))
	{
		printf("Unclosed quotes!\n");
		return (0);
	}
	exec_data_re_init(data);
	allocate_token_chain(cmd, data);
	fill_token_chain(cmd, data);
	type_token_chain(data);
	print_token_chain(data);
	printf("\n");
	token_chain_analyzer(data);
	print_token_chain(data);
//	executor(data);
//	free_token_chain(data);
	return (0);
}
