/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 20:04:38 by voparkan          #+#    #+#             */
/*   Updated: 2024/08/24 14:28:01 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"
#include "../../incl/executor.h"

void	iterate_commands(t_exec_bag *eb, t_data *data)
{
	while (eb->cur)
	{
		if (str_comp(eb->cur->type, "bu") && data->n_cmd == 0)
			execute_builtin(eb->cur, data);
		else if (str_comp(eb->cur->type, "vd"))
			envp_add_reallocate(data, eb->cur->token, 1);
		else if (str_comp(eb->cur->type, "pr") || str_comp(eb->cur->type, "bp"))
		{
			eb->run = true;
			break ;
		}
		eb->cur = eb->cur->next;
	}
}

void	executor_finished_clean(t_executor *pt, t_exec_bag *eb, t_data *data)
{
	free_alloc(pt);
	data->exec->cmd = NULL;
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
	data->n_cmd = 0;
	free(eb);
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
	if (exec_data_preparation(data) < 0)
		return (-1);
	eb = malloc(sizeof(t_exec_bag));
	if (eb == NULL)
		perror("unable allocate memory");
	init_exec_bag(eb, data, pt);
	fd_m = STDIN_FILENO;
	eb->run = true;
	// iterate_commands(eb, data);
	//pt->comm = data->exec->cmd;
	pt->append = data->exec->append;
	if (eb->run)
		e_c = ft_loop(pt, fd_m);
	executor_finished_clean(pt, eb, data);
	return (e_c);
}
