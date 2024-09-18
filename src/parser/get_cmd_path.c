/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 01:35:28 by smelicha          #+#    #+#             */
/*   Updated: 2024/09/18 13:10:42 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"
#include <stdbool.h>

void status_and_error(const char *pathcmd, char ***array, struct stat *st);

/**
 * Function to retrive executables path for particular command,
 * returns pointer to the string
 * RETURN OF THIS FUNCTION SHOULD NOT BE FREED AFTER USE IN CALLING FUNCTION!!!
 */
char	*get_cmd_path(const char *cmd, t_data *data)
{
	t_cmd_list	*current;
	char	*temp;
	char	*ret;

	if (!data->cmd_list || (is_binary_path((char *)cmd) == 2))
		return (ft_memdup(cmd));
	current = data->cmd_list->next;
	while (current)
	{
		if (str_comp(cmd, current->cmd))
			return (ft_memdup(current->full_path));
		else
			current = current->next;
	}
	if (is_binary_path((char *)cmd))
	{
		temp = ft_memdup(b_getenv("PWD", data));
		ret = ft_strjoin(temp, &cmd[1]);
		free(temp);
		return (ret);
	}
	if (is_builtin((char *)cmd, data))
		return (ft_memdup("builtin"));
	return (NULL);
}

bool	check_cmd_path_exists(const char *cmd, t_data *data)
{
	t_cmd_list	*current;

	if (!data->cmd_list)
		return (false);
	current = data->cmd_list->next;
	while (current)
	{
		if (str_comp(cmd, current->cmd))
			return (true);
		else
			current = current->next;
	}
	if (is_builtin((char *) cmd, data) || is_binary_path((char *) cmd))
		return (true);
	return (false);
}

void set_empty_array(char ***array)
{
	*array = malloc(1 * sizeof (char *));
	*array[0] = NULL;
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}

void	ft_check_access(char *pathcmd, char ***array, t_executor *pt)
{
	DIR			*dirname;
	struct stat	st;


	if (!pathcmd)
	{
		pt->parsing_ok = false;
		g_last_status = 127;
		return;
	}
	if (str_comp(pathcmd, "builtin"))
		return ;
	dirname = opendir(pathcmd);
	if (dirname)
	{
		closedir(dirname);
		set_empty_array(array);
		errno = EISDIR;
		perror(pathcmd);
		g_last_status = 126;
	}
	else if ((access(pathcmd, X_OK) == -1))
		status_and_error(pathcmd, array, &st);
}

void status_and_error(const char *pathcmd, char ***array, struct stat *st)
{
	if (!stat(pathcmd, st) && (*st).st_mode != S_IXUSR)
	{
		g_last_status = 126;
		errno = 13;
		perror(pathcmd);
	}
	else
	{
		g_last_status = 127;
		perror("Command not found");
	}
	set_empty_array(array);
}
