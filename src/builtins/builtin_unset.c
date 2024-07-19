/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:19:31 by smelicha          #+#    #+#             */
/*   Updated: 2024/07/19 18:20:22 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

//TODO Deleting the entry in envp or local temp envp from the var pos
int	unset(t_token_chain *current, t_data *data)
{
	int		var_pos;
	char	temp_flag;

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
	if (temp_flag)
		printf("variable from pos: %s\n", data->local_temp_envp[var_pos]);
	else
		printf("variable from pos: %s\n", data->envp[var_pos]);
	return (0);
}
