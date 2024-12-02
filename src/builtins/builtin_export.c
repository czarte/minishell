/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:20:41 by smelicha          #+#    #+#             */
/*   Updated: 2024/12/02 10:32:03 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

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

int	add_empty_variable(char *var, char temp, t_data *data)
{
	char	*new_var;
	int		var_len;

	var_len = ft_strlen(var);
	new_var = malloc(var_len + 2);
	ft_memcpy(new_var, var, var_len);
	new_var[var_len] = '=';
	new_var[var_len + 1] = '\0';
	if (export_from_token(new_var, temp, data))
	{
		free(new_var);
		return (-1);
	}
	free(new_var);
	return (0);
}

int	b_export_cont(char *cmd, char temp, t_data *data)
{
	if (!ft_contains_char(cmd, '='))
	{
		if (check_envp_for_dupl(data->local_temp_envp, cmd) >= 0)
		{
			envp_add_reallocate(data,
				data->local_temp_envp[check_envp_for_dupl(data->local_temp_envp,
					cmd)], temp);
		}
		else
		{
			if (add_empty_variable(cmd, temp, data))
			{
				g_last_status = 1;
				return (-1);
			}
		}
	}
	else if (export_from_token(cmd, temp, data))
	{
		g_last_status = 1;
		return (-1);
	}
	if (is_path(cmd))
		get_cmd_list(data);
	return (0);
}

int	b_export(char **cmd, char temp, t_data *data)
{
	while (str_comp(*cmd, "builtin") || str_comp(*cmd, "export"))
		cmd++;
	if (!*cmd)
		no_option_export(data->envp);
	while (*cmd)
	{
		if (forbidden_cahracters(*cmd))
			;
		else
		{
			if (b_export_cont(*cmd, temp, data))
				return (-1);
			else
				g_last_status = 0;
		}
		cmd++;
	}
	return (0);
}
