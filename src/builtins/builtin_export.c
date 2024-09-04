/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:20:41 by smelicha          #+#    #+#             */
/*   Updated: 2024/07/22 13:45:39 by smelicha         ###   ########.fr       */
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

int	export_from_token(char *var, t_data *data)
{
	if (envp_add_reallocate(data, var, 0))
	{
		perror("Export");
		return (-1);
	}
	return (0);
}

void	no_option_export(char **envp)
{
	int		i;
	int		j;
	bool	first_equal_sgn;

	i = 0;
	j = 0;
	while (envp[i])
	{
		write(1, "declare -x ", 12);
		first_equal_sgn = true;
		while (envp[i][j])
		{
			write(1, &envp[i][j], 1);
			if (envp[i][j] == '=' && first_equal_sgn)
			{
				write(1, "\"", 1);
				first_equal_sgn = false;
			}
			j++;
		}
		write(1, "\"\n", 2);
		j = 0;
		i++;
	}
}

bool	is_path(char *str)
{
	if (str[0] == 'P' && str[1] == 'A' && str[2] == 'T' && str[3] == 'H')
		return (true);
	return (false);
}

/**
 * note: export() is reserved
 */
int	b_export(char *var, t_data *data)
{
	int	temp_var_position;

	temp_var_position = 0;
	if (!ft_contains_char(var, '='))
	{
		temp_var_position = check_envp_for_duplicate(data->local_temp_envp,
				var);
		if (temp_var_position >= 0)
			envp_add_reallocate(data, data->local_temp_envp[temp_var_position],
				0);
		return (0);
	}
	if (export_from_token(var, data))
		return (-1);
	if (!var)
		no_option_export(data->envp);
	else if (is_path(var))
		get_cmd_list(data);
	g_last_status = 0;
	return (0);
}
