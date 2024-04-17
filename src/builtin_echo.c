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

	current = echo_tok->next;
	while (current && str_comp(current->type, "ar"))
	{
		printf(" %s", current->token);
		current = current->next;
	}
	printf("\n");
}
