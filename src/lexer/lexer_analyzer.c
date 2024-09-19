/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_analyzer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:51:34 by stepan            #+#    #+#             */
/*   Updated: 2024/09/19 11:08:37 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	set_redirections(t_token_chain *current, t_executor *pt, t_lex_cmd *lc)
{
	if (str_comp(current->type, "ri") && current->next)
	{
		type_token(current->next, "fp");
		if (pt->heredoc)
		{
			type_token(current, "ar");
			return ;
		}
		pt->infile = ft_memdup(current->next->token);
		add_to_collection((void *)pt->infile, pt);
		pt->heredoc = true;
		lc->dlmtr = '<';
	}
	if (str_comp(current->type, "rd") && current->next)
	{
		type_token(current->next, "dl");
		pt->dlmtr = ft_memdup(current->next->token);
		add_to_collection((void *)pt->dlmtr, pt);
		pt->heredoc_rl = true;
		lc->dlmtr = '<';
	}
	if (str_comp(current->type, "ro") && current->next)
	{
		type_token(current->next, "fp");
		pt->outfile = ft_memdup(current->next->token);
		add_to_collection((void *)pt->outfile, pt);
		lc->dlmtr = '>';
	}
	if (str_comp(current->type, "ra") && current->next)
	{
		type_token(current->next, "fp");
		pt->outfile = ft_memdup(current->next->token);
		add_to_collection((void *)pt->outfile, pt);
		pt->append = true;
		lc->dlmtr = '>';
	}
}

/**
 * Work in progress, will analyze pipes between programs
 */
int	analyze_redirections(t_data *data, t_executor *pt, t_lex_cmd *lc)
{
	t_token_chain	*current;

	lc->cmd = lc->cmd;
	current = data->token_chain->next;
	while (current)
	{
		set_redirections(current, pt, lc);
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
int	token_chain_analyzer(t_data *data, t_executor *pt)
{
	if (check_for_env_vars(data, pt))
		return (-1);
	if (check_for_binary_paths(data) < 0)
		return (-1);
	count_cmds(data);
	return (0);
}
