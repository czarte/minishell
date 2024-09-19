/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotes_pair_check.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 17:05:30 by smelicha          #+#    #+#             */
/*   Updated: 2024/08/06 18:07:52 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"
#include "../../incl/executor.h"

void	cmd_quotes_pair_check_cont(t_qps_data *qps, t_lex_cmd *lc)
{
	if (qps->quote && *qps->cmd == qps->quote)
	{
		lc->dlmtr = qps->quote;
		if (*qps->cmd == '"')
			qps->dq++;
		if (*qps->cmd == '\'')
			qps->sq++;
		qps->quote = '\0';
	}
	else if (!qps->quote && (*qps->cmd == '\"' || *qps->cmd == '\''))
	{
		if (!qps->first)
		{
			qps->first = true;
			qps->quote = *qps->cmd;
		}
		if (*qps->cmd == '"')
			qps->dq++;
		if (*qps->cmd == '\'')
			qps->sq++;
	}
}

int	cmd_quotes_pair_check_ret_logic(t_qps_data *qps, t_lex_cmd *lc)
{
	if (qps->dq % 2 || qps->sq % 2)
		return (0);
	else
	{
		if (((qps->dq == 2 && qps->sq == 0) && (lc->cmd[0] == '"')) \
			|| ((qps->sq == 2 && qps->dq == 0) && (lc->cmd[0] == '\'')))
			lc->dlmtr = '\0';
		else if (lc->dlmtr && !((lc->dlmtr == '"') || (lc->dlmtr == '\'')))
			lc->dlmtr = ' ';
		else if ((lc->dlmtr == '"') || (lc->dlmtr == '\''))
			return (1);
		else
			lc->dlmtr = ' ';
		return (1);
	}
}

/**
 * Checks for unclosed quotes in command
 * returns 1 if ok
 * returns 0 if ko
 */
int	cmd_quotes_pair_check(t_lex_cmd *lc)
{
	t_qps_data	qps;

	qps.dq = 0;
	qps.sq = 0;
	qps.cmd = lc->cmd;
	qps.quote = '\0';
	qps.first = false;
	while (qps.cmd && *qps.cmd)
	{
		cmd_quotes_pair_check_cont(&qps, lc);
		qps.cmd++;
	}
	return (cmd_quotes_pair_check_ret_logic(&qps, lc));
}
