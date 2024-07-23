/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:24:18 by voparkan          #+#    #+#             */
/*   Updated: 2024/07/20 14:21:07 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	tokens_len(t_token_chain *tokens)
{
	t_token_chain	*curr;
	int				len;

	curr = tokens;
	len = 0;
	while (curr && !str_comp(curr->type, "pi"))
	{
		len++;
		curr = curr->next;
	}
	return (len);
}
