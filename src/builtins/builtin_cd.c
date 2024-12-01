/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 01:35:47 by smelicha          #+#    #+#             */
/*   Updated: 2024/09/03 10:28:41 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	cd_update_envp(t_data *data)
{
	char	**env_var;

	env_var = malloc(sizeof(char *) * 3);
	if (!env_var)
		perror("Allocation in cd");
	else
	{
		env_var[2] = NULL;
		env_var[1] = ft_strjoin("PWD=", data->work_dir);
		env_var[0] = ft_memdup("builtin");
		b_export(env_var, 0, data);
		free_string_array(env_var);
	}
}

/**
 * Builtin cd command function, takes the argument as a string where the path
 * to the new working directory is specified, either absolute or relative
 */
void	cd(const char *new_wd, t_data *data)
{
	char	*home_relative;

	home_relative = NULL;
	if (!new_wd)
		new_wd = b_getenv("HOME", data);
	if (new_wd[0] == '~')
		home_relative = ft_strjoin(b_getenv("HOME", data), (new_wd + 1));
	if (!home_relative)
		g_last_status = chdir(new_wd);
	else
		g_last_status = chdir(home_relative);
	if (g_last_status != 0)
	{
		errno = 20;
		perror(new_wd);
		return ;
	}
	free(data->work_dir);
	data->work_dir = getcwd(NULL, 0);
	cd_update_envp(data);
	if (home_relative)
		free(home_relative);
}
