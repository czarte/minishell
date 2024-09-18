/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 20:04:38 by voparkan          #+#    #+#             */
/*   Updated: 2024/09/17 21:24:31 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"
#include "../../incl/executor.h"

void	executor_finished_clean(t_executor *pt, t_data *data)
{
	if (pt->debug)
		check_commands(pt);
	clean_garbage(pt);
	free_alloc(pt);
	data->n_cmd = 0;
	free(pt);
}

/**
 * Executes commands from token chain
 */
int	executor(t_data *data, t_executor *pt)
{
	t_exec_bag	*eb;
	int			fd_m;
	int			e_c;

	e_c = 0;

	eb = malloc(sizeof(t_exec_bag));
	add_to_collection((void *)eb, pt);
	if (eb == NULL)
		perror("unable allocate memory");
	fd_m = STDIN_FILENO;
	eb->run = true;
	pt->data = data;
	if (eb->run)
		e_c = ft_loop(pt, fd_m);
	executor_finished_clean(pt, data);
	return (e_c);
}
