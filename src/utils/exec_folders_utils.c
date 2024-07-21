/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_folders_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 18:07:40 by smelicha          #+#    #+#             */
/*   Updated: 2024/07/21 18:10:51 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

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
