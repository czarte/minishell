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

void	lexer_cont_1(t_lex_cmd *lc, t_data *data)
{
	int	ex_ret;

	ex_ret = 1;
	while (ex_ret)
		ex_ret = env_var_expander(lc, data);
	if (data->debug)
		printf("lc->cmd from lexer: %s\n", lc->cmd);
	free_token_chain(data);
//	 remove_unwanted_quotes(lc, '\'');
//	 remove_unwanted_quotes(lc, '"');
	if (!ft_strnchr(lc->cmd, '\'') && !ft_strnchr(lc->cmd, '"') \
		&& lc->dlmtr != '>' && lc->dlmtr != '<')
		lc->dlmtr = ' ';
}

t_lex_cmd	*lexer_cont(t_lex_cmd *lc, t_data *data, t_executor *pt)
{
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
	if (token_chain_analyzer(data) < 0)
		return (free(lc), NULL);
	lexer_cont_1(lc, data);
	return (lc);
}

/**
 * Takes command and processes it resulting in linked list of typed tokens
 * ready for execution
 */
t_lex_cmd	*lexer(char *cmd, t_data *data, t_executor *pt)
{
	t_lex_cmd	*lc;

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
	return (lexer_cont(lc, data, pt));
}
