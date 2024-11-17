/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_analyzer_utils_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:36:07 by smelicha          #+#    #+#             */
/*   Updated: 2024/07/22 14:22:34 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	expand_last_exit_status(t_token_chain *current)
{
	type_token(current, "ar");
	free(current->token);
	current->token = ft_itoa(g_last_status);
}

void	analyze_builtins_logic(t_token_chain *current)
{
	t_token_chain	*new_pipe;
	t_token_chain	*new_cat;

	new_pipe = malloc(sizeof(t_token_chain));
	new_pipe->token = ft_memdup("|");
	new_cat = malloc(sizeof(t_token_chain));
	new_cat->token = ft_memdup("cat");
	new_cat->next = current->next;
	new_pipe->next = new_cat;
	current->next = new_pipe;
}

void	analyze_builtin(t_token_chain *current, t_data *data)
{
	t_token_chain	*temp;

	temp = NULL;
	type_token(current, "bu");
	while (current->next && (!str_comp(current->next->token, ">")
			|| !str_comp(current->next->token, ">>")))
	{
		if (str_comp(current->next->token, ">")
			|| str_comp(current->next->token, ">>"))
			temp = current;
		current = current->next;
	}
	current = temp;
	if (!current)
		return ;
	if (str_comp(current->next->token, ">")
		|| str_comp(current->next->token, ">>"))
	{
		if (str_comp(current->next->token, ">>"))
			data->exec->append = true;
		analyze_builtins_logic(current);
	}
}
