/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token_type.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:51:42 by stepan            #+#    #+#             */
/*   Updated: 2024/09/08 15:55:51 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

t_token_chain	*prog_arg_fix_logic(t_token_chain *current, char *pr_ar)
{
	if ((str_comp(current->type, "pr") || str_comp(current->type, "bu")
			|| str_comp(current->type, "bp")) && !*pr_ar)
		*pr_ar = 1;
	else if (current && *pr_ar && (str_comp(current->type, "pi")))
		*pr_ar = 0;
	else if (current && *pr_ar && (str_comp(current->type, "pr")
			|| str_comp(current->type, "bu") || str_comp(current->type, "bp")
			|| str_comp(current->type, "vd")))
		type_token(current, "ar");
	if (current)
		current = current->next;
	return (current);
}

int	is_binary_path(char *token)
{
	if (ft_strlen(token) >= 2)
	{
		if (token[0] == '.' && token[1] == '/')
			return (1);
		else if (token[0] == '/')
			return (2);
	}
	return (0);
}

void set_binary_path_type(t_token_chain *current, bool heredoc)
{
	if (heredoc)
		type_token(current, "fp");
	else
		type_token(current, "bp");
}

void	type_token_logic(t_token_chain *current, t_data *data)
{
	bool	heredoc;
	heredoc = false;
	while (current)
	{
		if (str_comp(current->token, "<"))
		{
			type_token(current, "ri");
			heredoc = true;
		}
		else if (str_comp(current->token, ">"))
			type_token(current, "ro");
		else if (str_comp(current->token, "<<"))
			type_token(current, "rd");
		else if (str_comp(current->token, ">>"))
			type_token(current, "ra");
		else if (is_var_decl(current->token, data))
			type_token(current, "vd");
		else if (is_binary_path(current->token))
			set_binary_path_type(current, heredoc);
		else
			type_token(current, "ar");
		current = current->next;
	}
}

/**
 * Routine to type the token chain linked list
 */
int	type_token_chain(t_data *data, t_executor *pt, t_lex_cmd *lc)
{
	t_token_chain	*current;

	current = data->token_chain->next;
	if (current)
		type_token_logic(current, data);
	analyze_redirections(data, pt, lc);
	print_token_chain(data);
//	print_token_chain(data);
	return (0);
}
