/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_analyzer_utils_1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 19:00:47 by smelicha          #+#    #+#             */
/*   Updated: 2024/07/20 20:37:25 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

/**
 * Expands the environment variable and makes an argument from it
 */
int	expand_env_var(t_token_chain *current, t_data *data)
{
	char	*env_var;
	char	*new_token;

	env_var = NULL;
	new_token = NULL;
	env_var = b_getenv((current->token + 1), data);
	new_token = ft_memcpy(env_var);
	if (!new_token && env_var)
	{
		perror("Allocation of expanded env var");
		return (-1);
	}
	free(current->token);
	current->token = new_token;
	str_fill(current->type, "ar");
	return (0);
}

/**
 * Checks if the token chain contains environment variable to expand
 */
int	check_for_env_vars(t_data *data)
{
	t_token_chain	*current;

	current = data->token_chain->next;
	while (current)
	{
		if (str_comp(current->type, "ev"))
			if (expand_env_var(current, data))
				return (1);
		current = current->next;
	}
	return (0);
}

void	count_cmds(t_data *data)
{
	t_token_chain	*current;

	current = data->token_chain->next;
	while (current)
	{
		if (str_comp(current->type, "pr"))
			data->n_cmd++;
		current = current->next;
	}
}

int	count_slashes(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == '/')
			i++;
		str++;
	}
	return (i);
}

bool	binary_is_in_list(char *name, char *path, t_data *data)
{
	t_cmd_list	*cmd_list;
	t_cmd_list	*prev;

	cmd_list = data->cmd_list;
	prev = NULL;
	while (cmd_list)
	{
		if (str_comp(name, cmd_list->cmd))
		{
			if (str_comp(path, cmd_list->full_path))
				return (true);
			else if (prev)
			{
				prev->next = cmd_list->next;
				free(cmd_list->cmd);
				free(cmd_list->full_path);
				free(cmd_list);
				return (false);
			}
		}
		prev = cmd_list;
		cmd_list = cmd_list->next;
	}
	return (false);
}
