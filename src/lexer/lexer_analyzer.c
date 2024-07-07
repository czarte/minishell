/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_analyzer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:51:34 by stepan            #+#    #+#             */
/*   Updated: 2024/07/07 14:36:21 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

/**
 * Work in progress, will analyze pipes between programs
 */
int	analyze_redirections(t_data *data)
{
	t_token_chain	*current;

	current = data->token_chain->next;
	printf("Hello from redirections analyzer!\n");
	while (current)
	{
		if (str_comp(current->type, "ri") && current->next)
			type_token(current->next, "fp");
		if (str_comp(current->type, "rd") && current->next)
			type_token(current->next, "dl");
		if (str_comp(current->type, "ro") && current->next)
			type_token(current->next, "fp");
		if (str_comp(current->type, "ra") && current->next)
			type_token(current->next, "fp");
		current = current->next;
	}
	return (0);
}

char	*b_getenv(char *name, t_data *data)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (data->local_temp_envp && data->local_temp_envp[i])
	{
		while (data->local_temp_envp[i][j] == name[k])
		{
			j++;
			k++;
		}
		if (data->local_temp_envp[i][j] == '=')
			return (data->local_temp_envp[i] + j + 1);
		j = 0;
		k = 0;
		i++;
	}
	i = 0;
	while (data->envp && data->envp[i])
	{
		while (data->envp[i][j] == name[k])
		{
			j++;
			k++;
		}
		if (data->envp[i][j] == '=')
			return (data->envp[i] + j + 1);
		j = 0;
		k = 0;
		i++;
	}
	return (NULL);
}

/**
 * Expands the environment variable and makes an argument from it
 */
int	expand_env_var(t_token_chain *current, t_data *data)
{
	char	*env_var;
	char	*new_token;

	// var_name = current->token + 1;
	env_var = NULL;
	new_token = NULL;
	// printf("env var name: %s\n", var_name);
	env_var = b_getenv((current->token + 1), data);
	// printf("env var value: %s\n", env_var);
	new_token = ft_memcpy(env_var);
	if (!new_token && env_var)
	{
		perror("Allocation of expanded env var");
		return (-1);
	}
	// str_fill(new_token, env_var);
	free(current->token);
	// printf("new_token: %s\n", new_token);
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
	t_token_chain *current;

	current = data->token_chain->next;
	while (current)
	{
		if (str_comp(current->type, "pr"))
			data->n_cmd++;
		current = current->next;
	}
}
/**
 * Main analyzing function
 * TODO add flags to main struct while creating the token chain what it contains so the chain doesn't need to be scanned for each type, like for env vars...
 */
int	token_chain_analyzer(t_data *data)
{
	if (check_for_env_vars(data))
		return (-1);
	analyze_redirections(data);
	count_cmds(data);
	return (0);
}
