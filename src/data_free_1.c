/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_free_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 19:51:26 by smelicha          #+#    #+#             */
/*   Updated: 2024/07/21 19:51:48 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

char	**free_string_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
	return (array);
}

void	free_exec_files(t_data *data)
{
	if (data->exec->infile)
	{
		free(data->exec->infile);
		data->exec->infile = NULL;
	}
	if (data->exec->outfile)
	{
		free(data->exec->outfile);
		data->exec->outfile = NULL;
	}
}
