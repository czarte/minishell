/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_analyzer_utils_1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 19:00:47 by smelicha          #+#    #+#             */
/*   Updated: 2024/09/08 14:54:50 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

/**
 * Expands the environment variable and makes an argument from it
 */
int	expand_env_var(t_token_chain *current, t_data *data, t_executor *pt)
{
	char	*env_var;
	char	*new_token;

	env_var = NULL;
	new_token = NULL;
	pt->append = pt->append;	//dummy
	if (current->expand)
	{
		env_var = b_getenv((current->token + 1), data);
		new_token = ft_memdup(env_var);
		if (!new_token && env_var)
		{
			perror("Allocation of expanded env var");
			return (-1);
		}
		free(current->token);
		current->token = new_token;
	}
	str_fill(current->type, "ar");
	return (0);
}

/*
int	env_expanded_token_size(char *token, t_data *data)
{
	int		i;
	char	**vars;
	int		new_token_length;
	char	var_name_buff[256];

	new_token_length = 0;
	i = 0;
	while (*token)
	{
		while (*token != '$')
		{
			token++;
			new_token_length++;
		}
		while (ft_contains_char(" \"\'", *token))
		{
			var_name_buff[i] = *token;
			i++;
			token++;
		}
		var_name_buff[i] = '\0';
		new_token_length += ft_strlen(b_getenv(var_name_buff));
	}
	return (0);
}

int	expand_mid_sentence(t_token_chain *current, t_data *data)
{
	char	*env_var;
	char	*new_token;
	char	*old_token;

	env_var = NULL;
	new_token = NULL;
	old_token = current->token;
	new_token = malloc(env_expanded_token_size(old_token, data));
	if (!new_token)
	{
		perror("Allocation of expanded env var in token");
		return (-1);
	}
	return (0);
}
*/

/**
 * Checks if the token chain contains environment variable to expand
 */
int	check_for_env_vars(t_data *data, t_executor *pt)
{
	t_token_chain	*current;

	current = data->token_chain->next;
	while (current)
	{
		if (str_comp(current->type, "ev"))
		{
			if (expand_env_var(current, data, pt))
				return (1);
		}
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
