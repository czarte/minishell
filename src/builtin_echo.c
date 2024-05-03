/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stepan <stepan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:51:19 by stepan            #+#    #+#             */
/*   Updated: 2024/04/17 17:51:21 by stepan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

/**
 * Builtin echo command function, work in progress
 */
void	echo(t_token_chain *echo_tok)
{
	t_token_chain	*current;
	char			new_line;

	current = echo_tok->next;
	new_line = 1;
	if (current && str_comp(current->token, "-n"))
	{
		new_line = 0;
		current = current->next;
	}
	while (current && str_comp(current->type, "ar"))
	{
		write(1, current->token, ft_strlen(current->token));
		current = current->next;
		if (current)
			write(1, " ", 1);
	}
	if (new_line)
		write(1, "\n", 1);
}
