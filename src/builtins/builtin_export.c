/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:20:41 by smelicha          #+#    #+#             */
/*   Updated: 2024/07/19 18:21:37 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	export_from_local(t_data *data)
{
	if (envp_add_reallocate(data, data->local_temp_envp[0], 0))
	{
		perror("Export from local");
		return (-1);
	}
	free(data->local_temp_envp[0]);
	data->local_temp_envp[0] = NULL;
	return (0);
}

int	export_from_token(t_token_chain *current, t_data *data)
{
	if (envp_add_reallocate(data, current->token, 0))
	{
		perror("Export from token");
		return (-1);
	}
	return (0);
}

/**
 * Debug function
 */
void	print_envp(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
	{
		printf("NULL\n");
		return ;
	}
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
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

/**
 * note: export() is reserved
 */
int	b_export(t_token_chain *current, t_data *data)
{
	int	temp_var_position;

	temp_var_position = 0;
	if (current->next && !ft_contains_char(current->next->token, '='))
	{
		temp_var_position = check_envp_for_duplicate(data->local_temp_envp,
				current->next->token);
		if (temp_var_position >= 0)
			envp_add_reallocate(data, data->local_temp_envp[temp_var_position],
				0);
		return (0);
	}
	if (current->next)
	{
		if (export_from_token(current->next, data))
			return (-1);
	}
	if (!current->next)
		no_option_export(data->envp);
	return (0);
}
