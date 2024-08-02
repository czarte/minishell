/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token_type_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 17:05:30 by smelicha          #+#    #+#             */
/*   Updated: 2024/07/20 17:06:07 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	type_token(t_token_chain *token_node, char *type)
{
	int	i;

	i = 0;
	while (i != 3)
	{
		token_node->type[i] = type[i];
		i++;
	}
}

int	is_builtin(char *token, t_data *data)
{
	int	i;

	i = 0;
	while (i != 8)
	{
		if (str_comp(token, data->builtins[i]))
			return (1);
		i++;
	}
	return (0);
}

int	is_env_var(char *token)
{
	if (token[0] == '$' && token[1] != '?')
		return (1);
	return (0);
}

//TODO How to save last pipe output stream? :D
int	is_last_pipe_exit(char *token)
{
	if (token[0] == '$' && token[1] == '?' && !token[2])
		return (1);
	return (0);
}

int	is_var_decl(char *token, t_data *data)
{
	t_token_chain	*current;

	current = data->token_chain;
	while (current)
	{
		if (str_comp(current->token, "export"))
			return (0);
		current = current->next;
	}
	while ((*token >= 'A' && *token <= 'Z') || (*token >= '0' && *token <= '9')
		|| *token == '_')
		token++;
	if (*token == '=')
		return (1);
	return (0);
}
