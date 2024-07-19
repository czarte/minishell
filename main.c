/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 01:34:56 by smelicha          #+#    #+#             */
/*   Updated: 2024/07/19 18:47:03 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./incl/minishell.h"

pid_t	pid;

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	if (argc != 1)
		return (0);
	argv++;
	(void)argv;
	signals_init();
	data = malloc(sizeof(t_data));
	if (data == NULL)
	{
		perror("Main data struct: ");
		return (-1);
	}
	if (data_init(data, envp) == -1)
		return (-1);
	if (get_cmd_list(data) == -1)
		return (-1);
	cli(data);
	free_data(data);
	return (0);
}
