/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 17:52:43 by voparkan          #+#    #+#             */
/*   Updated: 2024/11/14 09:27:33 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	export_from_local(t_data *data)
{
	if (envp_add_reallocate(data, data->local_temp_envp[0], 0))
	{
		perror("Export");
		return (-1);
	}
	free(data->local_temp_envp[0]);
	data->local_temp_envp[0] = NULL;
	return (0);
}

int	export_from_token(char *var, char temp, t_data *data)
{
	if (envp_add_reallocate(data, var, temp))
	{
		perror("Export");
		return (-1);
	}
	return (0);
}

int	num_of_vars(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i] != NULL)
		i++;
	return (i);
}

int	copy_add_envp(char **new_envp, char **envp, char *new_var)
{
	int	i;

	i = 0;
	while (envp && envp[i])
	{
		new_envp[i] = ft_memdup(envp[i]);
		if (new_envp[i] == NULL)
		{
			perror("Copying envp");
			return (-1);
		}
		i++;
	}
	if (new_var)
	{
		new_envp[i] = ft_memdup(new_var);
		if (new_envp[i] == NULL)
		{
			perror("Copying envp");
			return (-1);
		}
	}
	return (0);
}

int	check_envp_for_dupl(char **envp, char *new_var)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!envp || !new_var)
		return (-1);
	while (envp[i])
	{
		while (envp[i][j] == new_var[j] && new_var[j] != '=')
			j++;
		if (envp[i][j] == '=' && (new_var[j] == '=' || new_var[j] == '\0'))
			return (i);
		j = 0;
		i++;
	}
	return (-1);
}
