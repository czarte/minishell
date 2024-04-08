/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 01:35:05 by smelicha          #+#    #+#             */
/*   Updated: 2024/04/06 23:10:29 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void free_cmd_list(t_data *data)
{
	t_cmd_list *tmp;
	t_cmd_list *current;

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

void free_token_chain(t_data *data)
{
	t_token_chain *tmp;
	t_token_chain *current;

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

int free_data(t_data *data)
{
	if (data->cmd_list)
		free_cmd_list(data);
	if (data->token_chain)
		free_token_chain(data);
	if (data->builtins)
		free_builtins(data);
	free(data->token_chain);
	free(data);
	return (0);
}

void	null_builtins(t_data *data)
{
	int	i;

	i = 0;
	while (i != 8)
	{
		data->builtins[i] = NULL;
		i++;
	}
}

void	fill_builtins(t_data *data)
{
	str_fill(data->builtins[0], "echo");
	str_fill(data->builtins[1], "cd");
	str_fill(data->builtins[2], "pwd");
	str_fill(data->builtins[3], "export");
	str_fill(data->builtins[4], "unset");
	str_fill(data->builtins[5], "env");
	str_fill(data->builtins[6], "exit");
}

int	allocate_builtins(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i != 8)
	{
		data->builtins[i] = malloc(sizeof(char) * 7);
		if (!data->builtins)
		{
			perror("allocating builtin string:");
			return (-1);
		}
		while (j != 7)
		{
			data->builtins[i][j] = '\0';
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

int	init_builtins(t_data *data)
{
	data->builtins = malloc(sizeof(char *) * 8);
	if (!data->builtins)
	{
		perror("builtins:");
		return (-1);
	}
	null_builtins(data);
	allocate_builtins(data);
	fill_builtins(data);
	return (0);
}

int data_init(t_data *data)
{
	data->cmd_list = NULL;
	data->token_chain = NULL;
	data->builtins = NULL;
	data->cmd_list = malloc(sizeof(t_cmd_list));
	if (data->cmd_list == NULL)
	{
		perror("cmd_list: ");
		free_data(data);
		return (-1);
	}
	data->cmd_list->cmd = NULL;
	data->cmd_list->full_path = NULL;
	data->cmd_list->next = NULL;
	data->last_c_l_node = data->cmd_list;
	data->token_chain = malloc(sizeof(t_token_chain));
	if (data->token_chain == NULL)
	{
		perror("cmd_list: ");
		free_data(data);
		return (-1);
	}
	data->token_chain->token = NULL;
	data->token_chain->next = NULL;
	getcwd(data->work_dir, sizeof(data->work_dir));
	init_builtins(data);
	return (0);
}

void free_folder_strs(char **folder_strs)
{
	int i;

	i = 0;
	while (folder_strs[i] != NULL)
	{
		free(folder_strs[i]);
		i++;
	}
	free(folder_strs);
}
