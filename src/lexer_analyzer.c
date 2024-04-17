/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_analyzer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stepan <stepan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:51:34 by stepan            #+#    #+#             */
/*   Updated: 2024/04/17 17:51:37 by stepan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

/**
 * Checks is there is even number of quotes in token chain, otherwise the command is invalid
 */
int	analyze_quotes(t_data *data)
{
	t_token_chain	*current;
	int				dq;
	int				sq;

	current = data->token_chain->next;
	dq = 0;
	sq = 0;
	while (current)
	{
		if (str_comp(current->type, "dq"))
			dq++;
		if (str_comp(current->type, "sq"))
			sq++;
		current = current->next;
	}
	printf("dq: %i\tsq: %i\n", dq, sq);
	if ((dq % 2) || (sq % 2))
		return (-1);
	return (0);
}

/**
 * Work in progress, will analyze pipes between programs
 */
int	analyze_pipes(t_data *data)
{
	t_token_chain	*current;

	current = data->token_chain->next;
	while (current)
	{
		current = current->next;
	}
	return (0);
}

int	token_chain_analyzer(t_data *data)
{
	if (analyze_quotes(data) < 0)
		return (-1);
	return (0);
}
