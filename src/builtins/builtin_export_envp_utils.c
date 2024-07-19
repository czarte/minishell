/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_envp_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 20:09:14 by smelicha          #+#    #+#             */
/*   Updated: 2024/07/19 20:13:42 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	update_envp_var(char **envp, char *new_var, int v_pos)
{
	int	i;

	i = 0;
	if (v_pos >= 0)
		printf("envp [%i] update original: %s\n", v_pos, envp[v_pos]);
	if (v_pos == -1)
		return (1);
	free(envp[v_pos]);
	envp[v_pos] = NULL;
	envp[v_pos] = malloc(ft_strlen(new_var) + 1);
	while (new_var[i])
	{
		envp[v_pos][i] = new_var[i];
		i++;
	}
	envp[v_pos][i] = '\0';
	return (0);
}

int	envp_add_reallocate_finish(char *new_var, char temp, t_data *data,
	t_envp_a_r_data *ardata)
{
	if (!ardata->new_envp)
	{
		perror("Envp reallocation");
		return (-1);
	}
	while (ardata->i != (ardata->n_o_v + 1))
	{
		ardata->new_envp[ardata->i] = NULL;
		ardata->i++;
	}
	if (copy_add_envp(ardata->new_envp, ardata->old_envp, new_var))
		return (-1);
	if (new_var)
		free_old_envp(ardata->old_envp);
	if (temp)
		data->local_temp_envp = ardata->new_envp;
	else
		data->envp = ardata->new_envp;
	return (0);
}

/**
 * Adds environment variable to the local environment
 * if temp == 0 it works with local environment
 * if temp == 1 it works with temporary variables declared by 'VAR=VALUE'
 */
int	envp_add_reallocate(t_data *data, char *new_var, char temp)
{
	t_envp_a_r_data	ardata;

	ardata.n_o_v = 0;
	ardata.i = 0;
	ardata.new_envp = NULL;
	ardata.ret = 0;
	if (temp)
		ardata.old_envp = data->local_temp_envp;
	else
		ardata.old_envp = data->envp;
	ardata.ret = update_envp_var(ardata.old_envp, new_var,
			check_envp_for_duplicate(ardata.old_envp, new_var));
	if (ardata.ret == 0 || ardata.ret == -1)
		return (ardata.ret);
	ardata.n_o_v = num_of_vars(ardata.old_envp);
	if (new_var)
		ardata.n_o_v++;
	ardata.new_envp = malloc(sizeof(char *) * (ardata.n_o_v + 1));
	return (envp_add_reallocate_finish(new_var, temp, data, &ardata));
}
