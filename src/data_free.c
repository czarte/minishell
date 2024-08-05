/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 19:48:11 by smelicha          #+#    #+#             */
/*   Updated: 2024/07/25 12:03:31 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

/**
 * Routine to free linked list with commands and paths to their binaries
 */
void	free_cmd_list(t_data *data)
{
	t_cmd_list	*tmp;
	t_cmd_list	*current;

	current = data->cmd_list->next;
	if (data->cmd_list->cmd)
		free(data->cmd_list->cmd);
	if (data->cmd_list->full_path)
		free(data->cmd_list->full_path);
	free(data->cmd_list);
	while (current)
	{
		tmp = current->next;
		if (current->cmd)
			free(current->cmd);
		if (current->full_path)
			free(current->full_path);
		free(current);
		current = tmp;
	}
}

/**
 * Routine to free linked list with tokens
 */
void	free_token_chain(t_data *data)
{
	t_token_chain	*tmp;
	t_token_chain	*current;

	current = data->token_chain->next;
	data->token_chain->next = NULL;
	if (data->token_chain->token)
		free(data->token_chain->token);
	while (current)
	{
		tmp = current->next;
		if (current->token)
			free(current->token);
		free(current);
		current = tmp;
	}
}

/**
 * Routine to free array with names of builtin commands
 */
void	free_builtins(t_data *data)
{
	int	i;

	i = 0;
	while (i != 8)
	{
		if (data->builtins[i])
			free(data->builtins[i]);
		i++;
	}
	free(data->builtins);
}

void	free_exec(t_data *data)
{
	t_list	*current;
	t_list	*next;

	current = data->exec->cmd;
	if (current)
		next = data->exec->cmd->next;
	while (current)
	{
		while (*current->content)
		{
			free(*current->content);
			current->content++;
		}
		current = next;
		if (current)
			next = current->next;
	}
	free(current);
	free(data->exec);
	data->exec = NULL;
}

/**
 * Main freeing routine
 */
int	free_data(t_data *data)
{
	if (data->cmd_list)
		free_cmd_list(data);
	if (data->token_chain)
		free_token_chain(data);
	if (data->builtins)
		free_builtins(data);
	if (data->envp)
		free_old_envp(data->envp);
	if (data->local_temp_envp)
		free_old_envp(data->local_temp_envp);
	free(data->token_chain);
	free(data);
	return (0);
}
