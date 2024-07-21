/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:19:31 by smelicha          #+#    #+#             */
/*   Updated: 2024/07/21 16:24:45 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	copy_remove_envp(char **new_envp, char **envp, int var_pos)
{
	int	i;

	i = 0;
	while (envp && envp[i])
	{
		new_envp[i] = ft_memcpy(envp[i]);
		if (new_envp[i] == NULL)
		{
			perror("Copying envp");
			return (-1);
		}
		i++;
		if (i == var_pos)
			i++;
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

char	**allocate_new_envp(int	n)
{
	char	**new_envp;

	new_envp = NULL;
	new_envp = malloc(sizeof(char*) * n);
	if (!new_envp)
		return (NULL);
	double_pointer_null_init(new_envp, n);
	return (new_envp);
}

//TODO Deleting the entry in envp or local temp envp from the var pos
int	unset(t_token_chain *current, t_data *data)
{
	int		var_pos;
	char	temp_flag;
	char	**new_envp;

	new_envp = NULL;
	if (!current->next)
		return (0);
	var_pos = check_envp_for_duplicate(data->envp, current->next->token);
	printf("var_pos from envp: %i\n", var_pos);
	if (var_pos >= 0)
		temp_flag = 0;
	if (var_pos < 0)
	{
		var_pos = check_envp_for_duplicate(data->local_temp_envp,
				current->next->token);
		printf("var_pos from temp: %i\n", var_pos);
		if (var_pos >= 0)
			temp_flag = 1;
	}
	printf("temp_flag: %i, var_pos: %i var_name: %s\n", temp_flag, var_pos,
		current->next->token);
	if (temp_flag == 1)
	{
		printf("variable from pos: %s\n", data->local_temp_envp[var_pos]);
		new_envp = allocate_new_envp(num_of_vars(data->local_temp_envp));
		copy_remove_envp(new_envp, data->local_temp_envp, var_pos);
		free_old_envp(data->local_temp_envp);
		data->local_temp_envp = new_envp;
	}
	else if (temp_flag == 0)
	{
		printf("variable from pos: %s\n", data->envp[var_pos]);
		new_envp = allocate_new_envp(num_of_vars(data->envp));
		copy_remove_envp(new_envp, data->envp, var_pos);
		free_old_envp(data->envp);
		data->envp = new_envp;
	}
	else
	{
		printf("Nothing to unset :(\n");
	}
	return (0);
}
