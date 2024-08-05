/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token_type.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:51:42 by stepan            #+#    #+#             */
/*   Updated: 2024/07/22 13:47:42 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

/**
 * Takes care of case when the argument of program is the name of another
 * program, all tokens between program/builtin and pipe/redirections that
 * are also name of program or builtin are retyped to argument
 */
void	prog_arg_fix(t_data *data)
{
	t_token_chain	*current;
	char			pr_ar;

	current = data->token_chain->next;
	pr_ar = 0;
	while (current)
	{
		if ((str_comp(current->type, "pr") || str_comp(current->type, "bu"))
			&& !pr_ar)
		{
			pr_ar = 1;
			current = current->next;
		}
		while (current && pr_ar && (str_comp(current->type, "pr")
				|| str_comp(current->type, "bu")))
		{
			type_token(current, "ar");
			current = current->next;
		}
		if (current && pr_ar && !(str_comp(current->type, "pr")
				|| str_comp(current->type, "bu")))
			pr_ar = 0;
		if (current)
			current = current->next;
	}
}

int	is_binary_path(char *token)
{
	if (ft_strlen(token) >= 2)
	{
		if (token[0] == '.' && token[1] == '/')
			return (1);
		else if (token[0] == '/')
			return (1);
	}
	return (0);
}

void	type_token_logic(t_token_chain *current, t_data *data)
{
	if (is_builtin(current->token, data))
		type_token(current, "bu");
	else if (get_cmd_path(current->token, data))
		type_token(current, "pr");
	else if (str_comp(current->token, "|"))
		type_token(current, "pi");
	else if (str_comp(current->token, "<"))
		type_token(current, "ri");
	else if (str_comp(current->token, ">"))
		type_token(current, "ro");
	else if (str_comp(current->token, "<<"))
		type_token(current, "rd");
	else if (str_comp(current->token, ">>"))
		type_token(current, "ra");
	else if (is_last_pipe_exit(current->token))
		expand_last_exit_status(current);
	else if (is_env_var(current->token))
		type_token(current, "ev");
	else if (is_var_decl(current->token, data))
		type_token(current, "vd");
	else if (is_binary_path(current->token))
		type_token(current, "bp");
	else
		type_token(current, "ar");
}

/**
 * Routine to type the token chain linked list
 */
void	type_token_chain(t_data *data)
{
	t_token_chain	*current;

	current = data->token_chain->next;
	while (current)
	{
		type_token_logic(current, data);
		current = current->next;
	}
	prog_arg_fix(data);
}
