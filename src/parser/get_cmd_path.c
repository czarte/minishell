/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 01:35:28 by smelicha          #+#    #+#             */
/*   Updated: 2024/10/28 14:43:11 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"
#include <stdbool.h>

void	status_and_error(const char *pathcmd, char ***array, struct stat *st);

/**
 * Function to retrive executables path for particular command,
 * returns pointer to the string
 * RETURN OF THIS FUNCTION SHOULD NOT BE FREED AFTER USE IN CALLING FUNCTION!!!
 */
char	*get_cmd_path(const char *cmd, t_data *data)
{
	t_cmd_list	*current;
	char		*temp;
	char		*ret;

	if (is_builtin((char *)cmd, data) || is_var_decl((char *)cmd, data))
		return (ft_memdup("builtin"));
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
	return (NULL);
}

bool	check_cmd_path_exists(const char *cmd, t_data *data)
{
	t_cmd_list	*current;

	if (is_builtin((char *) cmd, data) || is_binary_path((char *) cmd) || is_var_decl((char *)cmd, data))
		return (true);
	if (!data->cmd_list)
		return (false);
	current = data->cmd_list->next;
	if (*cmd == '"' && cmd[ft_strlen(cmd) - 1] == '"')
		cmd_trim((char *) cmd, '"');
	if (*cmd == '\'' && cmd[ft_strlen(cmd) - 1] == '\'')
		cmd_trim((char *) cmd, '\'');
	while (current)
	{
		if (str_comp(cmd, current->cmd))
			return (true);
		else
			current = current->next;
	}
	return (false);
}

void	ft_check_access(char *pathcmd, char ***array, t_executor *pt)
{
	DIR			*dirname;
	struct stat	st;

	if (pt->debug)
		printf("pathcmd from ft_check_access: %s\n", pathcmd);
	if (!pathcmd)
	{
		pt->parsing_ok = false;
		g_last_status = 127;
		return ;
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

void	status_and_error(const char *pathcmd, char ***array, struct stat *st)
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
		perror("command not found");
	}
	set_empty_array(array);
}
