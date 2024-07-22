/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:21:54 by smelicha          #+#    #+#             */
/*   Updated: 2024/07/22 13:45:02 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	env(t_data *data)
{
	int		i;
	char	**envp;

	i = 0;
	envp = data->envp;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	g_last_status = 0;
}
