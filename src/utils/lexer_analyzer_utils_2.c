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
