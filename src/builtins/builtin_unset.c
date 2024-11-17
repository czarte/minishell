/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:19:31 by smelicha          #+#    #+#             */
/*   Updated: 2024/11/14 09:27:33 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	copy_remove_envp(char **new_envp, char **envp, int var_pos, int n)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	n++;
	if (new_envp == NULL || var_pos < 0)
		return (0);
	while (j < n)
	{
		if (j == var_pos)
			j++;
		new_envp[i] = ft_memdup(envp[j]);
		if (new_envp[i] == NULL)
			return (-1);
		i++;
		j++;
	}
	return (0);
}

void	double_pointer_null_init(char **arr, int n)
{
	int	i;

	i = 0;
	while (i != n)
	{
		arr[i] = NULL;
		i++;
	}
}

char	**allocate_new_envp(int n)
{
	char	**new_envp;

	new_envp = NULL;
	if (n > 1)
	{
		new_envp = malloc(sizeof(char *) * n);
		if (!new_envp)
			return (NULL);
		double_pointer_null_init(new_envp, n);
	}
	return (new_envp);
}

int	finish_unset(int var_pos, char **new_envp, char temp_flag, t_data *data)
{
	if (temp_flag == 1)
	{
		new_envp = allocate_new_envp(num_of_vars(data->local_temp_envp));
		copy_remove_envp(new_envp, data->local_temp_envp, var_pos,
			(num_of_vars(data->envp) - 1));
		free_old_envp(data->local_temp_envp);
		data->local_temp_envp = new_envp;
	}
	else if (temp_flag == 0)
	{
		new_envp = allocate_new_envp(num_of_vars(data->envp));
		copy_remove_envp(new_envp, data->envp, var_pos,
			(num_of_vars(data->envp) - 1));
		free_old_envp(data->envp);
		data->envp = new_envp;
	}
	return (0);
}

//TODO Deleting the entry in envp or local temp envp from the var pos
int	unset(char *var, t_data *data)
{
	int		var_pos;
	char	temp_flag;
	char	**new_envp;

	new_envp = NULL;
	var_pos = check_envp_for_dupl(data->envp, var);
	if (var_pos >= 0)
		temp_flag = 0;
	if (var_pos < 0)
	{
		var_pos = check_envp_for_dupl(data->local_temp_envp, var);
		if (var_pos >= 0)
			temp_flag = 1;
	}
	if (var_pos < 0)
		return (0);
	if (str_comp(var, "PATH"))
		free_cmd_list(data);
	return (finish_unset(var_pos, new_envp, temp_flag, data));
}
