/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_folders.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 11:07:34 by voparkan          #+#    #+#             */
/*   Updated: 2024/08/07 23:50:53 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_folders.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 01:35:34 by smelicha          #+#    #+#             */
/*   Updated: 2024/07/21 18:10:06 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"
/**
 * Debug function
 */

// void	print_cmd_list(t_data *data)
// {
// 	t_cmd_list	*current;

// 	current = data->cmd_list->next;
// 	while (current)
// 	{
// 		printf("cmd: %s, path: %s\n", current->cmd, current->full_path);
// 		current = current->next;
// 	}
// }

/**
 * Allocates memory for a node in a linked list anf fills it with data,
 * which are name of the command and path to its executable
 */
int	add_cmd_list_node(char *name, char *path, t_data *data)
{
	if (!data->cmd_list)
		allocate_for_binary(data);
	if (name[0] == '.')
		return (0);
	data->last_c_l_node->next = malloc(sizeof(t_cmd_list));
	if (!data->last_c_l_node->next)
	{
		perror("Adding cmd_list node");
		return (-1);
	}
	data->last_c_l_node = data->last_c_l_node->next;
	data->last_c_l_node->next = NULL;
	data->last_c_l_node->cmd = ft_memdup(name);
	data->last_c_l_node->full_path = ft_join_path(path, name);
	return (0);
}

/**
 * Scans the folders for executables it contains
 */
int	scan_folder(struct dirent *dirent, char **folder_strs, DIR *dir,
	t_data *data)
{
	while (dirent != NULL)
	{
		if (check_exec_access(*folder_strs, dirent))
		{
			if (add_cmd_list_node(dirent->d_name, *folder_strs, data) < 0)
				return (-1);
		}
		dirent = readdir(dir);
	}
	return (0);
}

int	scan_folders(char **folder_strs, t_data *data)
{
	DIR				*dir;
	struct dirent	*dirent;

	dir = NULL;
	dirent = NULL;
	while (*folder_strs)
	{
		dir = opendir(*folder_strs);
		if (dir == NULL)
		{
			if (*folder_strs)
			{
				folder_strs++;
				continue ;
			}
			else
				break ;
		}
		dirent = readdir(dir);
		if (scan_folder(dirent, folder_strs, dir, data) < 0)
			return (-1);
		closedir(dir);
		folder_strs++;
	}
	return (0);
}

int	get_folders(char *path, char **folder_strs)
{
	char	*current_str;

	while (*path)
	{
		*folder_strs = malloc(sizeof(char) * (fpl(path) + 1));
		if (*folder_strs == NULL)
		{
			perror("Folder str: ");
			return (-1);
		}
		current_str = *folder_strs;
		while (*path != ':' && *path)
		{
			*current_str = *path;
			path++;
			current_str++;
		}
		*current_str = '\0';
		if (*path)
			path++;
		folder_strs++;
	}
	return (0);
}

/**
 * Main routine to get list of commands and path to their executables in
 * current environment
 */
int	get_cmd_list(t_data *data)
{
	char	*path;
	char	**folder_strs;

	folder_strs = NULL;
	path = NULL;
	path = b_getenv("PATH", data);
	if (path == NULL)
		return (0);
	folder_strs = malloc(sizeof(char *) * (get_number_of_folders(path) + 1));
	if (folder_strs == NULL)
	{
		perror("Folder strings: ");
		return (-1);
	}
	folder_strs[get_number_of_folders(path)] = NULL;
	init_folder_strs(folder_strs, get_number_of_folders(path));
	get_folders(path, folder_strs);
	scan_folders(folder_strs, data);
	free_string_array(folder_strs);
	return (0);
}
