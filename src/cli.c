/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 18:17:28 by smelicha          #+#    #+#             */
/*   Updated: 2024/04/06 18:26:34 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	cli(t_data *data)
{
	char	*cmd;

	data = data;
	while (1)
	{
		cmd = readline(">:");
		printf("%s\n", cmd);
		if (str_comp(cmd, "exit"))
		{
			free(cmd);
			break ;
		}
		free(cmd);
	}
	return (1);
}
