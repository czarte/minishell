/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 01:35:05 by smelicha          #+#    #+#             */
/*   Updated: 2024/04/02 01:35:09 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

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

int	free_data(t_data *data)
{
	if (data->cmd_list)
		free_cmd_list(data);
	free(data);
	return (0);
}

int	data_init(t_data *data)
{
	data->cmd_list = NULL;
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
	getcwd(data->work_dir, sizeof(data->work_dir));
	return (0);
}

void	free_folder_strs(char **folder_strs)
{
	int	i;

	i = 0;
	while (folder_strs[i] != NULL)
	{
		free(folder_strs[i]);
		i++;
	}
	free(folder_strs);
}
