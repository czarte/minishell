/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_analyzer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:51:34 by stepan            #+#    #+#             */
/*   Updated: 2024/08/06 17:28:20 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	set_redirections(t_data *data, t_token_chain *current)
{
	if (str_comp(current->type, "ri") && current->next)
	{
		type_token(current->next, "fp");
		data->exec->infile = strdup(current->next->token);
	}
	if (str_comp(current->type, "rd") && current->next)
	{
		type_token(current->next, "dl");
		data->exec->dlmtr = strdup(current->next->token);
	}
	if (str_comp(current->type, "ro") && current->next)
	{
		type_token(current->next, "fp");
		data->exec->outfile = ft_memcpy(current->next->token);
	}
	if (str_comp(current->type, "ra") && current->next)
	{
		type_token(current->next, "fp");
		data->exec->outfile = ft_memcpy(current->next->token);
	}
}

/**
 * Work in progress, will analyze pipes between programs
 */
int	analyze_redirections(t_data *data)
{
	t_token_chain	*current;

	current = data->token_chain->next;
	while (current)
	{
		set_redirections(data, current);
		current = current->next;
	}
	return (0);
}

/**
 * Main analyzing function
 * TODO add flags to main struct while creating the token chain what it
 * contains so the chain doesn't need to be scanned for each type,
 * like for env vars...
 */
int	token_chain_analyzer(t_data *data)
{
	if (check_for_env_vars(data))
		return (-1);
	if (check_for_binary_paths(data) < 0)
		return (-1);
	count_cmds(data);
	return (0);
}
