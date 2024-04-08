/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 22:10:07 by smelicha          #+#    #+#             */
/*   Updated: 2024/04/06 23:09:00 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	print_token_chain(t_data *data)
{
	t_token_chain	*current;

	current = data->token_chain->next;
	while (current)
	{
		printf("token: %s\ttype: %s\n", current->token, current->type);
		current = current->next;
	}
}

int	number_of_tokens(char *cmd)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (cmd[i])
	{
		while (cmd[i] && cmd[i] == ' ')
			i++;
		if (cmd[i])
			n++;
		while (cmd[i] && cmd[i] != ' ')
			i++;
	}
	return (n);
}

int	token_length(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] && cmd[i] != ' ')
		i++;
	return (i);
}

void	type_token(t_token_chain *token_node, char *type)
{
	int	i;

	i = 0;
	while (i != 3)
	{
		token_node->type[i] = type[i];
		i++;
	}
}

/*
 TODO finish token typing logic
 */

int	is_builtin(char *token, t_data *data)
{
	int	i;

	i = 0;
	while (i != 7)
	{
		if (str_comp(token, data->builtins[i]))
			return (1);
		i++;
	}
	return (0);
}

int	is_env_var(char *token)
{
	if (token[0] == '$' && token[1] != '?')
		return (1);
	return (0);
}

int	is_last_pipe_exit(char *token)
{
	if (token[0] == '$' && token[1] == '?' && !token[2])
		return (1);
	return (0);
}

/*
 TODO when parsing cmd to tokens, trat " and ' characters
 as single tokens
 */

void	type_token_chain(t_data *data)
{
	t_token_chain	*current;

	current = data->token_chain->next;
	while (current)
	{
		if (is_builtin(current->token, data))
			type_token(current, "bu");
		else if (get_cmd_path(current->token, data))
			type_token(current, "pr");
		else if (str_comp(current->token, "|"))
			type_token(current, "pi");
		else if (str_comp(current->token, "<"))
			type_token(current, "ri");
		else if (str_comp(current->token, ">"))
			type_token(current, "ro");
		else if (str_comp(current->token, "<<"))
			type_token(current, "rd");
		else if (str_comp(current->token, ">>"))
			type_token(current, "ra");
		else if (is_last_pipe_exit(current->token))
			type_token(current, "es");
		else if (is_env_var(current->token))
			type_token(current, "ev");
		else if (str_comp(current->token, "\""))
			type_token(current, "dq");
		else if (str_comp(current->token, "\'"))
			type_token(current, "sq");
		else
			type_token(current, "ar");
		current = current->next;
	}
}

int	fill_token_chain(char *cmd, t_data *data)
{
	t_token_chain	*current;
	char			*token;

	current = data->token_chain->next;
	while (*cmd && *cmd == ' ')
		cmd++;
	while (current)
	{
		current->token = malloc(sizeof(char) * (token_length(cmd) + 1));
		if (current->token == NULL)
		{
			perror("token allocation:");
			return (-1);
		}
		token = current->token;
		while (*cmd && *cmd != ' ')
		{
			*token = *cmd;
			token++;
			cmd++;
		}
		*token = '\0';
		while (*cmd && *cmd == ' ')
			cmd++;
		current = current->next;
	}
	return (0);
}

int	allocate_token_chain(char *cmd, t_data *data)
{
	int			i;
	t_token_chain	*prev;
	t_token_chain	*current;

	i = number_of_tokens(cmd);
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

int	lexer(char *cmd, t_data *data)
{
	data = data;

	printf("cmd from lexer: %s\n", cmd);
	printf("number of tokens: %i\n", number_of_tokens(cmd));
	allocate_token_chain(cmd, data);
	fill_token_chain(cmd, data);
	type_token_chain(data);
	print_token_chain(data);
	free_token_chain(data);
	return (0);
}
