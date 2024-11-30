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

bool	is_cap_alpha(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (true);
	return (false);
}

bool	is_low_alpha(char c)
{
	if (c >= 'a' && c <= 'z')
		return (true);
	return (false);
}

bool	is_num(char c)
{
	if (c >= '0' && c <= '9')
		return (true);
	return (false);
}

bool	forbidden_cahracters(char *var)
{
	char	*tmp_var;

	tmp_var = var;
	printf("from forbidden char test: |%s|\n", tmp_var);
	if (!var)
		return (false);
	while (*var && *var != '=')
	{
		printf("checking: %c\n", *var);
		if (is_cap_alpha(*var) || is_low_alpha(*var) || is_num(*var)
			|| *var == '_' || *var == '=')
			var++;
		else
		{
			printf("forbidden found\n");
			return (true);
		}
	}
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

/**
 * note: export() is reserved
 */
int	b_export(char **cmd, char temp, t_data *data)
{
	int	i;

	i = 0;
	printf("From export:%c%p\n", temp, data);
	while (cmd[i])
	{
		printf("cmd[%i]: |%s|\n", i, cmd[i]);
		i++;
	}
	printf("\n");
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
			if (!ft_contains_char(*cmd, '='))
			{
				if (check_envp_for_dupl(data->local_temp_envp, *cmd) >= 0)
				{
					envp_add_reallocate(data,
						data->local_temp_envp[check_envp_for_dupl(data->local_temp_envp,
							*cmd)], temp);
				}
				else
				{
					if (add_empty_variable(*cmd, temp, data))
					{
						printf("returning fault from add empty var\n");
						g_last_status = 1;
						return (-1);
					}
				}
			}
			if (export_from_token(*cmd, temp, data))
			{
				g_last_status = 1;
				return (-1);
			}
			if (is_path(*cmd))
				get_cmd_list(data);
		}
		cmd++;
	}
	g_last_status = 0;
	return (0);
}
