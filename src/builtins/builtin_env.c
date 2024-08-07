/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:21:54 by smelicha          #+#    #+#             */
/*   Updated: 2024/07/22 13:45:02 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

char	*get_env_check_temp(char *name, t_data *data)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (data->local_temp_envp && data->local_temp_envp[i])
	{
		while (data->local_temp_envp[i][j] == name[k])
		{
			j++;
			k++;
		}
		if (data->local_temp_envp[i][j] == '=')
			return (data->local_temp_envp[i] + j + 1);
		j = 0;
		k = 0;
		i++;
	}
	return (NULL);
}

char	*get_env_check_envp(char *name, t_data *data)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (data->envp && data->envp[i])
	{
		while (data->envp[i][j] == name[k])
		{
			j++;
			k++;
		}
		if (data->envp[i][j] == '=')
			return (data->envp[i] + j + 1);
		j = 0;
		k = 0;
		i++;
	}
	return (NULL);
}

char	*b_getenv(char *name, t_data *data)
{
	char	*res;

	res = NULL;
	res = get_env_check_envp(name, data);
	return (res);
}

void	env(t_data *data)
{
	int		i;
	char	**envp;

	i = 0;
	envp = data->envp;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	g_last_status = 0;
}
