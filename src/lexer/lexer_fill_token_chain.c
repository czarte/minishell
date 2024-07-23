/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_fill_token_chain.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:25:06 by smelicha          #+#    #+#             */
/*   Updated: 2024/07/20 16:29:41 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	fill_token_chain_if_quote(t_fill_t_c_data *ftcdata)
{
	ftcdata->quote = *ftcdata->cmd;
	ftcdata->cmd++;
	while (*ftcdata->cmd && *ftcdata->cmd != ftcdata->quote)
	{
		*ftcdata->token = *ftcdata->cmd;
		ftcdata->token++;
		ftcdata->cmd++;
	}
	ftcdata->cmd++;
}

void	fill_token_chain_no_quote(t_fill_t_c_data *ftcdata)
{
	while (*ftcdata->cmd && *ftcdata->cmd != ' '
		&& !(*ftcdata->cmd == '\"' || *ftcdata->cmd == '\''))
	{
		*ftcdata->token = *ftcdata->cmd;
		ftcdata->token++;
		ftcdata->cmd++;
	}
}

void	fill_token_chain_data_manipulation(t_fill_t_c_data *ftcdata)
{
	ftcdata->token = ftcdata->current->token;
	if (*ftcdata->cmd == '\"' || *ftcdata->cmd == '\'')
		fill_token_chain_if_quote(ftcdata);
	else
		fill_token_chain_no_quote(ftcdata);
	*ftcdata->token = '\0';
	while (*ftcdata->cmd && *ftcdata->cmd == ' ')
		ftcdata->cmd++;
	ftcdata->current = ftcdata->current->next;
}

/**
 * Tokenizes command and saves it to the linked list of tokens for
 * further processing
 */
int	fill_token_chain(char *command, t_data *data)
{
	t_fill_t_c_data	ftcdata;

	ftcdata.current = data->token_chain->next;
	ftcdata.quote = '\0';
	ftcdata.cmd = command;
	while (ftcdata.cmd && *ftcdata.cmd && *ftcdata.cmd == ' ')
		ftcdata.cmd++;
	while (ftcdata.current)
	{
		ftcdata.current->token = malloc(sizeof(char)
				* (token_length(ftcdata.cmd) + 1));
		if (ftcdata.current->token == NULL)
		{
			perror("token allocation:");
			return (-1);
		}
		fill_token_chain_data_manipulation(&ftcdata);
	}
	return (0);
}
