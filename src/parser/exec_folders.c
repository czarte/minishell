/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_folders.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 01:35:34 by smelicha          #+#    #+#             */
/*   Updated: 2024/07/20 21:40:27 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"
/**
 * Debug function
 */

void	print_cmd_list(t_data *data)
{
	t_cmd_list	*current;

	current = data->cmd_list->next;
	while (current)
	{
		printf("cmd: %s, path: %s\n", current->cmd, current->full_path);
		current = current->next;
	}
}

/**
 * Allocates memory for a node in a linked list anf fills it with data,
 * which are name of the command and path to its executable
 */
int	add_cmd_list_node(char *name, char *path, t_data *data)
{
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
	data->last_c_l_node->cmd = ft_memcpy(name);
	data->last_c_l_node->full_path = ft_strjoin(path, name);
	return (0);
}

int	check_exec_access(char *folder, struct dirent *dirent)
{
	char	*path_to_check;
	char	*temp;

	temp = ft_strjoin(folder, "/");
	path_to_check = ft_strjoin(temp, dirent->d_name);
	free (temp);
	if (access(path_to_check, X_OK))
	{
		free(path_to_check);
		return (0);
	}
	free(path_to_check);
	return (1);
}

/**
 * Scans the folders for executables it contains
 */
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
		while (dirent != NULL)
		{
			if (check_exec_access(*folder_strs, dirent))
				add_cmd_list_node(dirent->d_name, *folder_strs, data);
			dirent = readdir(dir);
		}
		closedir(dir);
		folder_strs++;
	}
	return (0);
}

// file path length
int	fpl(char *path)
{
	int	i;

	i = 0;
	while (*path != ':' && *path)
	{
		i++;
		path++;
	}
	return (i);
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
 * Gets number of folders that should contain executables, delimited by ':'
 */
int	get_number_of_folders(char *path)
{
	int	i;

	i = 1;
	while (*path)
	{
		if (*path == ':')
			i++;
		path++;
	}
	return (i);
}

void	init_folder_strs(char **folder_strs, int num_of_flds)
{
	int	i;

	i = 0;
	while (i != num_of_flds)
	{
		folder_strs[i] = NULL;
		i++;
	}
}

//char *ft_getenv(char *path, t_data *data)
//{
//	(void)path;
//	char **envpath = ft_split((const char *) data->envp, '=');
//	free(envpath[0]);
//	return (envpath[1]);
//}
/**
 * Main routine to get list of commands and path to their executables in current environment
 */
int	get_cmd_list(t_data *data)
{
	char	*path;
	char	**folder_strs;

	folder_strs = NULL;
	path = NULL;
	path = getenv("PATH");
	if (path == NULL)
	{
		perror("Path: ");
		return (-1);
	}
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
	free_folder_strs(folder_strs);
	return (0);
}
