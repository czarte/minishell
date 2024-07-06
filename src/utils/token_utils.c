/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: voparkan <voparkan@student.42prague.cz>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:24:18 by voparkan          #+#    #+#             */
/*   Updated: 2024/07/06 18:34:39 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int 	tokens_len(t_token_chain *tokens)
{
	t_token_chain	*curr;
	int				len;

	curr = tokens;
	len = 0;
	while (curr)
	{
		len++;
		curr = curr->next;
	}
	return (len);
}