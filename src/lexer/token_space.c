/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: voparkan <voparkan@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by voparkan          #+#    #+#             */
/*   Updated: 2024/08/05 21:08:34 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	not_sp_pi_lsgt_before(char *cmd)
{
	return (*(cmd - 1) != ' ' && (*cmd == '|' || *cmd == '>' || *cmd == '<'));
}

int	not_sp_pi_lsgt_after(char *cmd)
{
	return (*(cmd + 1) != ' ' && (*cmd == '|' || *cmd == '>' || *cmd == '<'));
}

int	not_sp_pi_lsgt(char *cmd)
{
	return ((*cmd == '>' || *cmd == '<') && \
	(*(cmd + 1) == '>' || *(cmd + 1) == '<'));
}

t_token_bag	*init_token_bag(t_token_bag *tb)
{
	tb->quote = '\0';
	tb->first_run = true;
	return (tb);
}

int	no_space_tokens(char *cmd)
{
	t_token_bag	tb;
	int			n;

	n = 0;
	init_token_bag(&tb);
	while (cmd && *cmd)
	{
		if (*cmd == '\"' || *cmd == '\'')
		{
			tb.quote = *cmd;
			cmd++;
			while (*cmd && *cmd != tb.quote)
				cmd++;
		}
		if (!tb.first_run && not_sp_pi_lsgt_before(cmd))
			n++;
		if (*cmd && not_sp_pi_lsgt_after(cmd))
			n++;
		if (not_sp_pi_lsgt(cmd))
			cmd += 2;
		cmd++;
		tb.first_run = false;
	}
	return (n);
}
