/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 01:34:56 by smelicha          #+#    #+#             */
/*   Updated: 2024/04/06 18:25:07 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./incl/minishell.h"

pid_t	g_pid;
int		g_last_status;

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
	loop(data);
	free_data(data);
	return (0);
}
