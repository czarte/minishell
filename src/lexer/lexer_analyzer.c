/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_analyzer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:51:34 by stepan            #+#    #+#             */
/*   Updated: 2024/08/02 09:06:17 by voparkan         ###   ########.fr       */
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
	while (current)
	{
		if (str_comp(current->type, "ri") && current->next)
		{
			type_token(current->next, "fp");
			printf("token: %s, next: %p, next-type: %s, next-token: %s\n", current->token, current->next, current->next->type, current->next->token);
			if (data->exec->infile == NULL) {
				printf("lexer - data->exec->infile: %p\n", data->exec->infile);
			}
			data->exec->infile = strdup(current->next->token);
		}
		if (str_comp(current->type, "rd") && current->next)
			type_token(current->next, "dl");
		if (str_comp(current->type, "ro") && current->next)
		{
			type_token(current->next, "fp");
			data->exec->outfile = ft_memcpy(current->next->token);
		}
		if (str_comp(current->type, "ra") && current->next)
			type_token(current->next, "fp");
		current = current->next;
	}
	return (0);
}

char	*get_env_check_temp(char *name, t_data *data)
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
	return (NULL);
}

char	*get_env_check_envp(char *name, t_data *data)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
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

char	*b_getenv(char *name, t_data *data)
{
	char	*res;

	res = NULL;
	res = get_env_check_envp(name, data);
	if (!res)
		res = get_env_check_temp(name, data);
	return (res);
}

/**
 * Main analyzing function
 * TODO add flags to main struct while creating the token chain what it
 * contains so the chain doesn't need to be scanned for each type,
 * like for env vars...
 */
int	token_chain_analyzer(t_data *data)
{
	if (check_for_env_vars(data))
		return (-1);
	analyze_redirections(data);
	check_for_binary_paths(data);
	count_cmds(data);
	return (0);
}
