/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 22:10:07 by smelicha          #+#    #+#             */
/*   Updated: 2024/09/19 10:46:52 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"
#include "../../incl/executor.h"

/**
 * Returns length of token string in command, uses spaces for delimiter
 */
int	token_length(char *cmd)
{
	int		i;
	char	quote;

	i = check_for_no_space_token(cmd);
	quote = '\0';
	if (i)
		return (i);
	if (cmd[i] == '\"' || cmd[i] == '\'')
	{
		quote = cmd[i];
		i++;
		while (cmd[i] != quote)
			i++;
		return (i - 1);
	}
	while (cmd[i] && cmd[i] != ' ')
	{
		if (cmd[i] == '\"' || cmd[i] == '\'')
			break ;
		i++;
	}
	return (i);
}

/**
 * Allocates linked list for all tokens present in command
 */
int	allocate_token_chain(t_lex_cmd *lc, t_data *data)
{
	int				i;
	t_token_chain	*prev;
	t_token_chain	*current;

	i = number_of_tokens(lc->cmd);
	current = NULL;
	prev = data->token_chain;
	while (i)
	{
		current = malloc(sizeof(t_token_chain));
		if (!current)
		{
			perror("token_chain: ");
			return (-1);
		}
		current->next = NULL;
		current->token = NULL;
		prev->next = current;
		prev = current;
		current = NULL;
		i--;
	}
	return (0);
}

/**
 * Checks for unclosed quotes in command
 * returns 1 if ok
 * returns 0 if ko
 */
int	cmd_quotes_pair_check(t_lex_cmd *lc)
{
	int		dq;
	int		sq;
	char	quote;
	char	*cmd;
	bool	first;

	dq = 0;
	sq = 0;
	cmd = lc->cmd;
	quote = '\0';
	first = false;
	while (cmd && *cmd)
	{
		if (quote && *cmd == quote)
		{
			lc->dlmtr = quote;
			if (*cmd == '"')
				dq++;
			if (*cmd == '\'')
				sq++;
			quote = '\0';
		}
		else if (!quote && (*cmd == '\"' || *cmd == '\''))
		{
			if (!first) {
				first = true;
				quote = *cmd;
			}
			if (*cmd == '"')
				dq++;
			if (*cmd == '\'')
				sq++;
		}
		cmd++;
	}
	if (dq % 2 || sq % 2) {
		return (0);
	}
	else
	{
		if (((dq == 2 && sq == 0) && (lc->cmd[0] == '"')) || ((sq == 2 && dq == 0) && (lc->cmd[0] == '\'')))
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

bool	only_char(char *str, char c)
{
	if (!str)
		return(true);
	while (*str)
	{
		if (*str != c)
			return (false);
		str++;
	}
	return (true);
}

void	cmd_trim(char *cmd, char c)
{
	int	i;
	int	last_space_pos;
    char    *src;
    bool    first_letter;

	if (only_char(cmd, c))
		return ;
	i = 0;
	last_space_pos = 0;
    first_letter = false;
    src = NULL;
	if (!cmd || !*cmd)
		return ;
	while (cmd[i])
	{
        if (!first_letter && (cmd[i] != c))
        {
            src = (cmd + i);
            first_letter = true;
        }
		if (i)
		{
			if (cmd[i] == c && cmd[i - 1] != c)
				last_space_pos = i;
		}
		i++;
	}
	if (cmd[i - 1] == c)
		cmd[last_space_pos] = '\0';
    ft_memmove(cmd, src, (ft_strlen(src) + 1));
}

int	ft_strnchr(char *str, char c)
{
	char 	*s;
	int		i;

	i = 0;
	s = str;
	while (*s)
	{
		if ((*s == c) && (s != str))
			i++;
		s++;
	}
	return (i);
}

char **check_unwanted_quotes(char *cmd, char qt)
{
	char	*ptr;
	char	*end;
	char 	**ptrs;
	char 	**tmp;
	int		cnt;
	char	cntr;
	char	*last_char;

	cnt = ft_strnchr(cmd, qt);
	last_char = cmd + ft_strlen(cmd);
	cntr = '"';
	if (qt == '"')
		cntr = '\'';
	if (cnt) {
		ptrs = malloc((cnt + 1) * sizeof(ptrs));
		while (cnt)
		{
			ptrs[cnt] = NULL;
			cnt--;
		}
	}
	else
		return NULL;
	end = cmd;
	while (*end)
		end++;
	tmp = ptrs;
	ptr = cmd;
	while (*ptr && ptr < last_char)
	{
		if (*ptr == cntr) {
			ptr++;
			while (*ptr != cntr && ptr < last_char)
				ptr++;
		}
		if ((*ptr == qt) && ((ptr > cmd) && (ptr < end)) && (*(ptr - 1) != ' ') && (*(ptr + 1) != ' '))
		{
			*ptrs = ptr;
			ptrs++;
		}
		if (ptr < last_char)
			ptr++;
	}
	ptrs = tmp;
	return (ptrs);
}

void remove_unwanted_quotes(t_lex_cmd *lc, char qt) {
	char **qts;
	char **tmpqts;
	char *tmp;

	qts = check_unwanted_quotes(lc->cmd, qt);
	if (!qts)
		return ;
	tmp = lc->cmd;
	tmpqts = qts;
	while (*qts)
	{
		while (*lc->cmd)
		{
			if (*qts && (lc->cmd == *qts) && (**qts == qt)) {
//				printf("dest: %s\n", lc->cmd);
//				printf("src: %s\n", lc->cmd + 1);
//				printf("len: %d\n", ft_strlen(lc->cmd + 1));
				ft_memmovev(lc->cmd, lc->cmd + 1, ft_strlen(lc->cmd + 1) + 1);
				qts--;
				break;
			}
			lc->cmd++;
		}
		qts++;
	}
	lc->cmd = tmp;
	free(tmpqts);
}

/**
 * Takes command and processes it resulting in linked list of typed tokens
 * ready for execution
 */
t_lex_cmd	*lexer(char *cmd, t_data *data, t_executor *pt)
{
	t_lex_cmd	*lc;
	int			ex_ret;

	ex_ret = 1;
	if (data->debug)
		printf("printing PT (%p) before doing lexer thing\n", pt);
	print_t_executor(pt);
	pt->pwd = b_getenv("PWD", data);
	lc = malloc(sizeof(t_lex_cmd));
	if (!lc)
		return (NULL);
	lc->cmd = cmd;
	lc->dlmtr = ' ';
	if (data->debug)
		printf("lc->cmd from lexer: %s\n", lc->cmd);
	if (!cmd_quotes_pair_check(lc))
	{
		data->parse_fail = true;
		printf("Unclosed quotes!\n");
		free(lc);
		return (NULL);
	}
	cmd_trim(lc->cmd, ' ');
	allocate_token_chain(lc, data);
	fill_token_chain(lc->cmd, data);
	if (type_token_chain(data, pt, lc) < 0)
		return (free(lc), NULL);
	if (token_chain_analyzer(data, pt) < 0)
		return (free(lc), NULL);
	while (ex_ret)
		ex_ret = env_var_expander(lc, data);
	if (data->debug)
		printf("lc->cmd from lexer: %s\n", lc->cmd);
	free_token_chain(data);
	remove_unwanted_quotes(lc, '\'');
//	printf("result unwanted: %s\n", lc->cmd);
	remove_unwanted_quotes(lc, '"');
//	printf("result unwanted: %d\n", ft_strnchr(lc->cmd, '\'') % 2);
	if (!ft_strnchr(lc->cmd, '\'') && !ft_strnchr(lc->cmd, '"') && lc->dlmtr != '>' && lc->dlmtr != '<')
		lc->dlmtr = ' ';
	return (lc);
}
