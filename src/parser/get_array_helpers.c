/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_array_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: voparkan <voparkan@student.42prague.cz>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 12:31:58 by voparkan          #+#    #+#             */
/*   Updated: 2024/09/19 13:07:34 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"
#include "../../incl/executor.h"

int	exit_cmd_unexisted(t_bagp *psr, t_data *data)
{
	ft_putstr_fd(psr->splitcmd[0], 2);
	ft_putstr_fd(": Command not found\n", 2);
	data->parse_fail = true;
	g_last_status = 1;
	return (-1);
}

void	add_temp_to_cmd(t_bagp *psr, char **tmp)
{
	int		i;
	char	*temp;

	i = 0;
	temp = NULL;
	while (tmp[i])
	{
		temp = ft_strjoin(psr->combined, "\x15");
		add_to_collection((void *)temp, psr->pt);
		psr->combined = ft_strjoin(temp, tmp[i]);
		add_to_collection((void *)psr->combined, psr->pt);
		i++;
	}
}

void	init_tbags_bag(t_bags *tb, char const *s)
{
	tb->count = 0;
	tb->last_char = (char *)s + ft_strlen(s);
	tb->quote = '\0';
	tb->in_word = 0;
}

size_t	ft_skip_quote_token_len(char const *s, char c)
{
	size_t	len;
	char	quote;

	quote = '\0';
	len = 0;
	len = compute_quotes_token_len(s, c, len, quote);
	return (len);
}

int	iterate_quotes(const char *s, int c, int i, char quote)
{
	while (i > 0)
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			quote = s[i];
			i--;
			while ((s[i] && s[i] != quote) && i > 0)
				i--;
			quote = '\0';
		}
		if (s[i] == (char) c)
			break ;
		i--;
	}
	return (i);
}
