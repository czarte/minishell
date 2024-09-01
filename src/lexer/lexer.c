/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 22:10:07 by smelicha          #+#    #+#             */
/*   Updated: 2024/08/06 17:37:58 by smelicha         ###   ########.fr       */
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
	{
		return (i);
	}
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
	// if (i > )
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

	dq = 0;
	sq = 0;
	cmd = lc->cmd;
	quote = '\0';
	while (cmd && *cmd)
	{
		if (*cmd == '\"')
		{
			if (!quote)
				quote = *cmd;
			dq++;
		}
		else if (*cmd == '\'')
		{
			if (!quote)
				quote = *cmd;
			sq++;
		}
		cmd++;
	}
	if (dq % 2 || sq % 2)
		return (0);
	else
	{
		if (quote)
			lc->dlmtr = quote;
		else
			lc->dlmtr = ' ';
		return (1);
	}
}

void	cmd_space_trim(char *cmd)
{
	int	i;
	int	last_space_pos;
    char    *src;
    bool    first_letter;

	i = 0;
	last_space_pos = 0;
    first_letter = false;
    src = NULL;
	if (!cmd || !*cmd)
		return ;
	while (cmd[i])
	{
        if ((!first_letter && cmd[i] != ' '))
        {
            if (!first_letter)
                src = (cmd + i);
            first_letter = true;
        }
		if (i)
		{
			if (cmd[i] == ' ' && cmd[i - 1] != ' ')
				last_space_pos = i;
		}
		i++;
	}
	if (cmd[i - 1] == ' ')
		cmd[last_space_pos] = '\0';
    cmd = ft_memmove(cmd, src, (ft_strlen(src) + 1));
}

// void cmd_space_trim(char *cmd)
// {
//     char *dest;
//     char *src;
//     int len;
//
//     len = 0;
//     dest = cmd;
//     while (*cmd == ' ')
//         cmd++;
//     src = cmd;
//     while(*cmd !='\0')
//     {
//         cmd++;
//         len++;
//     }
//     while(*cmd == ' ')
//     {
//         cmd--;
//         len--;
//     }
//     ft_memmove(dest, src, len);
// 	dest[len] = '\0';
//     cmd = dest;
// }

/**
 * Takes command and processes it resulting in linked list of typed tokens
 * ready for execution
 */
t_lex_cmd	*lexer(char *cmd, t_data *data, t_executor *pt)
{
	t_lex_cmd	*lc;

	printf("printing PT before doing lexer thing\n");
	print_t_executor(pt);
	pt->pwd = b_getenv("PATH", data);
	lc = malloc(sizeof(t_lex_cmd));
	if (!lc)
		return (NULL);
	lc->cmd = cmd;
	printf("lc->cmd from lexer: %s\n", lc->cmd);
	if (!cmd_quotes_pair_check(lc))
	{
		printf("Unclosed quotes!\n");
		return (free(lc), NULL);
	}
	cmd_space_trim(lc->cmd);
	// exec_data_re_init(data);
	allocate_token_chain(lc, data);
	fill_token_chain(lc->cmd, data);
	if (type_token_chain(data, pt, lc) < 0)
		return (free(lc), NULL);
	// if (data->debug)
	// 	print_token_chain(data);
	if (token_chain_analyzer(data, pt) < 0)
		return (free(lc), NULL);
	// if (data->debug)
	print_token_chain(data);
	printf("lc->cmd from lexer: %s\n", lc->cmd);
	return (lc);
}
