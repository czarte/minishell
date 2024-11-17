/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:20:41 by smelicha          #+#    #+#             */
/*   Updated: 2024/11/14 09:29:45 by smelicha         ###   ########.fr       */
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

bool	forbidden_characters_err_mes(char *var, char *tmp_var)
{
	ft_putstr_fd("export: \'", 2);
	if (!*var)
		ft_putstr_fd(tmp_var, 2);
	else
		ft_putstr_fd(var, 2);
	ft_putstr_fd("\': not a valid identifier\n", 2);
	g_last_status = 1;
	return (true);
}

bool	forbidden_cahracters(char *var)
{
	char	*tmp_var;

	tmp_var = var;
	if (!var)
		return (false);
	while (1)
	{
		if (*var == '=' && var != tmp_var)
			return (false);
		if ((('A' <= *var) && ('Z' >= *var))
			|| (('a' <= *var) && ('z' >= *var))
			|| (('0' <= *var) && ('9' >= *var))
			|| *var == '_' || *var != '\0')
			var++;
		else
			return (forbidden_characters_err_mes(var, tmp_var));
	}
	return (false);
}

/**
 * note: export() is reserved
 */
int	b_export(char *var, char temp, t_data *data)
{
	if (!var)
		no_option_export(data->envp);
	if (forbidden_cahracters(var))
		return (-1);
	if (!ft_contains_char(var, '='))
	{
		if (check_envp_for_dupl(data->local_temp_envp, var) >= 0)
			envp_add_reallocate(data,
				data->local_temp_envp[check_envp_for_dupl(data->local_temp_envp,
					var)], temp);
		g_last_status = 0;
		return (0);
	}
	if (export_from_token(var, temp, data))
	{
		g_last_status = 1;
		return (-1);
	}
	if (is_path(var))
		get_cmd_list(data);
	g_last_status = 0;
	return (0);
}
