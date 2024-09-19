/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_rm_unwanted_quotes.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 17:05:30 by smelicha          #+#    #+#             */
/*   Updated: 2024/08/06 18:07:52 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"
#include "../../incl/executor.h"

void	check_unwanted_quotes_cont(t_uq_data *uq, char *cmd, char qt)
{
	while (*uq->ptr && uq->ptr < uq->last_char)
	{
		if (*uq->ptr == uq->cntr)
		{
			uq->ptr++;
			while (*uq->ptr != uq->cntr && uq->ptr < uq->last_char)
				uq->ptr++;
		}
		if ((*uq->ptr == qt) && ((uq->ptr > cmd) && (uq->ptr < uq->end)) \
			&& (*(uq->ptr - 1) != ' ') && (*(uq->ptr + 1) != ' '))
		{
			*uq->ptrs = uq->ptr;
			uq->ptrs++;
		}
		if (uq->ptr < uq->last_char)
			uq->ptr++;
	}
	uq->ptrs = uq->tmp;
}

char	**check_unwanted_quotes(char *cmd, char qt)
{
	t_uq_data	uq;

	uq.cnt = ft_strnchr(cmd, qt);
	uq.last_char = cmd + ft_strlen(cmd);
	uq.cntr = '"';
	if (qt == '"')
		uq.cntr = '\'';
	if (uq.cnt)
	{
		uq.ptrs = malloc((uq.cnt + 1) * sizeof(uq.ptrs));
		while (uq.cnt)
		{
			uq.ptrs[uq.cnt] = NULL;
			uq.cnt--;
		}
	}
	else
		return (NULL);
	uq.end = cmd;
	while (*uq.end)
		uq.end++;
	uq.tmp = uq.ptrs;
	uq.ptr = cmd;
	check_unwanted_quotes_cont(&uq, cmd, qt);
	return (uq.ptrs);
}

void	remove_unwanted_quotes(t_lex_cmd *lc, char qt)
{
	char	**qts;
	char	**tmpqts;
	char	*tmp;

	qts = check_unwanted_quotes(lc->cmd, qt);
	if (!qts)
		return ;
	tmp = lc->cmd;
	tmpqts = qts;
	while (*qts)
	{
		while (*lc->cmd)
		{
			if (*qts && (lc->cmd == *qts) && (**qts == qt))
			{
				ft_memmovev(lc->cmd, lc->cmd + 1, ft_strlen(lc->cmd + 1) + 1);
				qts--;
				break ;
			}
			lc->cmd++;
		}
		qts++;
	}
	lc->cmd = tmp;
	free(tmpqts);
}
