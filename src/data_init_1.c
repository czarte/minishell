/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 19:54:19 by smelicha          #+#    #+#             */
/*   Updated: 2024/07/21 19:56:43 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

/**
 * Null initialization for array with names of builtin commands
 */
void	null_builtins(t_data *data)
{
	int	i;

	i = 0;
	while (i != 8)
	{
		data->builtins[i] = NULL;
		i++;
	}
}

/**
 * Fills names of the builtin command into the array
 */
void	fill_builtins(t_data *data)
{
	str_fill(data->builtins[0], "echo");
	str_fill(data->builtins[1], "cd");
	str_fill(data->builtins[2], "pwd");
	str_fill(data->builtins[3], "export");
	str_fill(data->builtins[4], "unset");
	str_fill(data->builtins[5], "env");
	str_fill(data->builtins[6], "exit");
}

/**
 * Allocates memory forstrings in array with builtin commands
 */
int	allocate_builtins(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i != 8)
	{
		data->builtins[i] = malloc(sizeof(char) * 7);
		if (!data->builtins)
		{
			perror("allocating builtin string:");
			return (-1);
		}
		while (j != 7)
		{
			data->builtins[i][j] = '\0';
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}
