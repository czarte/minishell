/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 22:10:07 by smelicha          #+#    #+#             */
/*   Updated: 2024/09/01 18:55:59 by voparkan         ###   ########.fr       */
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

bool	is_var_char(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9') || c == '_' || c == '?')
		return (true);
	return (false);
}

void	insert_env_join_strings(char *res, char *main1, char *main2, char *add)
{
	int	i;

	i = 0;
	while(main1[i])
	{
		*res = main1[i];
		res++;
		i++;
	}
	i = 0;
	if (add)
	{
		while (add[i])
		{
			*res = add[i];
			res++;
			i++;
		}
		free(add);
	}
	i = 0;
	while (main2[i])
	{
		*res = main2[i];
		res++;
		i++;
	}
	*res = '\0';
}

char	*insert_env_string(int pos, char *main, char *add)
{
	char	*main1;
	char	*main2;
	char	*res;
	int		i;

	i = 0;
	main1 = malloc(sizeof(char) * (pos + 1));
	main2 = malloc(sizeof(char) * ft_strlen((main + pos)) + 1);
	res = malloc(sizeof(char) * (ft_strlen(main) + ft_strlen(add) + 1));
	while (*main != '$')
	{
		main1[i] = *main;
		printf("main1: %c\n", main1[i]);
		main++;
		i++;
	}
	main1[i] = '\0';
	main++;		//step over $
	i = 0;
	while (is_var_char(*main))
	{
		printf("main: %c\n", *main);
		main++;
	}
	while (*main)
	{
		main2[i] = *main;
		main++;
		i++;
	}
	main2[i] = '\0';
	i = 0;
	insert_env_join_strings(res, main1, main2, add);
	free(main1);
	free(main2);
	return (res);
}

int	ft_expandable(char *cmd)
{
	int	j;

	j = 0;
	while (*cmd)
	{
		if (*cmd == '\'')
		{
			cmd++;
			printf("single quote detected!!\n");
			while (*cmd && *cmd != '\'')
			{
				cmd++;
				j++;
			}
		}
		if (*cmd == '$')
		{
			printf("is expandable\n");
			return (j);
		}
		if (*cmd)
		{
			cmd++;
			j++;
		}
	}
	printf("nothing to expand\n");
	return (-1);
}

int	expander_of_last_exit(int d_p, t_lex_cmd *lc)
{
	char	*tmp;

	tmp = lc->cmd;
	if (*(lc->cmd + d_p + 1) != '?')
		return (-1);
	lc->cmd = insert_env_string(d_p, lc->cmd, ft_itoa(g_last_status));
	printf("last exit: %s\n", lc->cmd);
	free(tmp);
	return (0);
}

char	*get_var_name(int d_p, t_lex_cmd *lc)
{
	char	*tmp;
	char	*var_name;
	int		i;

	var_name = NULL;
	i = 0;
	tmp = (lc->cmd + d_p + 1);
	while (*tmp != ' ' && *tmp != '\0')
	{
		tmp++;
		i++;
	}
	var_name = malloc(sizeof(char) * (i + 1));
	tmp = (lc->cmd + d_p + 1);
	i = 0;
	while (is_var_char(*tmp))
	{
		var_name[i] = *tmp;
		tmp++;
		i++;
	}
	var_name[i] = '\0';
	return (var_name);
}

int	expander_of_env_var(int	d_p, t_lex_cmd *lc, t_data *data)
{
	char	*var_name;
	char	*tmp;

	var_name = NULL;
	tmp = lc->cmd;
	if (!expander_of_last_exit(d_p, lc))
		return (0);
	var_name = get_var_name(d_p, lc);
	lc->cmd = insert_env_string(d_p, lc->cmd, ft_memdup(b_getenv(var_name, data)));
	free(tmp);
	free(var_name);
	return (0);
}

int	env_var_expander(t_lex_cmd *lc, t_data *data)
{
	int	dollar_pos;

	data->builtins = data->builtins;	//DUMMY
	dollar_pos = ft_expandable(lc->cmd);
	printf("dollar_pos: %i\n", dollar_pos);
	if (dollar_pos < 0)
	{
		printf("returning from expander\n");
		return (0);
	}
	expander_of_env_var(dollar_pos, lc, data);
	printf("expander: %s\n", lc->cmd);
	return (1);
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
	printf("printing PT before doing lexer thing\n");
	print_t_executor(pt);
	pt->pwd = b_getenv("PWD", data);
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
	while (ex_ret)
		ex_ret = env_var_expander(lc, data);
	printf("lc->cmd from lexer: %s\n", lc->cmd);
	return (lc);
}
