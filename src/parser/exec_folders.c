/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_folders.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 11:57:48 by voparkan          #+#    #+#             */
/*   Updated: 2024/07/06 13:14:15 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_folders.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 01:35:34 by smelicha          #+#    #+#             */
/*   Updated: 2024/04/02 01:35:45 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"
/**
 * Debug function
 */
// void	print_folders(char **folder_strs)
// {
// 	int	i;
//
// 	i = 0;
// 	while (*folder_strs)
// 	{
// 		printf("folder %i: |%s|\n", i, *folder_strs);
// 		folder_strs++;
// 		i++;
// 	}
// }

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
	if (access(path_to_check, ))
	
	free(path_to_check);
	return (1);
}

/**
 * Scans the folders for executables it contains
 */
int		scan_folders(char **folder_strs, t_data *data)
{
	DIR				*dir;
	int				i;
	struct dirent	*dirent;

	i = 0;
	(void)i;
	dir = NULL;
	dirent = NULL;
	while (*folder_strs)
	{
		// TODO fix this function so it won't fail when dir in path does not exists or user has no access rights
		//printf("opening: %s\n", *folder_strs);
		dir = opendir(*folder_strs);
		if (dir == NULL)
			break ;
		dirent = readdir(dir);
		//printf("dirent %p\n", dirent);
		while (dirent != NULL)
		{
			//printf("filename: %s, type: %i\n", dirent->d_name, dirent->d_type);
			if (/*access(ft_strjoin(ft_strjoin(*folder_strs, "/"), dirent->d_name), X_OK)*/ 1)
			{
				//printf("filename: %s, type: %i\n", dirent->d_name, dirent->d_type);
				add_cmd_list_node(dirent->d_name, *folder_strs, data);
			}
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
			// printf("%c", *path);
			*current_str = *path;
			//printf("%c\n", *current_str);
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
	// printf("%s\n", path);
	// printf("number of folders to scan: %i\n", get_number_of_folders(path));
	//print_folders(folder_strs);
	scan_folders(folder_strs, data);
	free_folder_strs(folder_strs);
	return (0);
}
