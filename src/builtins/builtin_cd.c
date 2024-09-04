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

/**
 * Builtin cd command function, takes the argument as a string where the path
 * to the new working directory is specified, either absolute or relative
 */
void	cd(const char *new_wd, t_data *data)
{
	char	*env_var;

	if (chdir(new_wd) != 0)
	{
		perror("cd perrror");
		return ;
	}
	free(data->work_dir);
	data->work_dir = getcwd(NULL, 0);
	env_var = ft_strjoin("PWD=", data->work_dir);
	b_export(env_var, data);
	free(env_var);
	g_last_status = 0;
}
