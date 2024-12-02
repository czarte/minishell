/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 01:35:47 by smelicha          #+#    #+#             */
/*   Updated: 2024/12/02 10:57:03 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	cd_update_envp(t_data *data, char *home_relative)
{
	char	**env_var;

	free(data->work_dir);
	data->work_dir = getcwd(NULL, 0);
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
	if (home_relative)
		free(home_relative);
}

void	cd_too_many_arg_err(void)
{
	ft_putstr_fd("minishell: cd: too many arguments\n", 2);
	g_last_status = 1;
}

/**
 * Builtin cd command function, takes the argument as a string where the path
 * to the new working directory is specified, either absolute or relative
 */
void	cd(char **cmd, t_data *data)
{
	char	*home_relative;

	home_relative = NULL;
	if (!cmd[2])
		cmd[2] = b_getenv("HOME", data);
	else if (cmd[3])
	{
		cd_too_many_arg_err();
		return ;
	}
	if (cmd[2][0] == '~')
		home_relative = ft_strjoin(b_getenv("HOME", data), (cmd[2] + 1));
	if (!home_relative)
		g_last_status = chdir(cmd[2]) * -1;
	else
		g_last_status = chdir(home_relative) * -1;
	if (g_last_status != 0)
	{
		if (home_relative)
			free(home_relative);
		errno = 20;
		perror(cmd[2]);
		return ;
	}
	cd_update_envp(data, home_relative);
}
