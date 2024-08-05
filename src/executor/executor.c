/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: voparkan <voparkan@student.42prague.cz>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 20:04:38 by voparkan          #+#    #+#             */
/*   Updated: 2024/08/05 19:58:05 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"
#include "../../incl/executor.h"

void	exec_data_prep_fill(t_data *data, t_token_chain **tc, int *i)
{
	char			**cmd;
	int				arg_count;

	arg_count = command_arg_count(*tc, data);
	cmd = malloc(sizeof(char *) * (arg_count + 3));
	cmd[arg_count + 2] = NULL;
	cmd[0] = get_cmd_path((*tc)->token, data);
	cmd[1] = ft_memcpy((*tc)->token);
	*tc = (*tc)->next;
	while (*tc && str_comp((*tc)->type, "ar"))
	{
		cmd[(*i)] = ft_memcpy((*tc)->token);
		if ((*tc)->next && str_comp((*tc)->next->type, "ar"))
		{
			*tc = (*tc)->next;
			(*i)++;
		}
		else
			break ;
	}
	ft_lstadd_back(&data->exec->cmd, ft_lstnew((void *)cmd));
}

int	exec_data_preparation(t_data *data)
{
	t_token_chain	*tc;
	int				i;

	tc = data->token_chain->next;
	i = 2;
	while (tc)
	{
		if (tc->next && str_comp(tc->type, "ri"))
		{
			tc = tc->next;
			continue ;
		}
		if (str_comp(tc->type, "pr") || str_comp(tc->type, "bu"))
			exec_data_prep_fill(data, &tc, &i);
		if (tc && str_comp(tc->type, "ra"))
			data->exec->append = true;
		if (tc && str_comp(tc->type, "rd"))
			data->exec->limit = true;
		if (tc)
			tc = tc->next;
	}
	return (0);
}

void	assign_pt(t_data *data, t_executor *pt)
{
	if (data->exec->infile)
	{
		pt->infile = data->exec->infile;
		pt->heredoc = true;
	}
	else
		pt->infile = NULL;
	if (data->exec->outfile)
		pt->outfile = data->exec->outfile;
	else
		pt->outfile = NULL;
	if (data->exec->dlmtr)
	{
		pt->heredoc_rl = true;
		pt->dlmtr = data->exec->dlmtr;
	}
	pt->pwd = getenv("PWD");
	pt->deubg = data->debug;
}

void	iterate_commands(t_exec_bag *eb, t_data *data)
{
	while (eb->cur)
	{
		if (str_comp(eb->cur->type, "bu"))
			execute_builtin(eb->cur, data);
		else if (str_comp(eb->cur->type, "vd"))
			envp_add_reallocate(data, eb->cur->token, 1);
		else if (str_comp(eb->cur->type, "pr"))
		{
			eb->run = true;
			break ;
		}
		eb->cur = eb->cur->next;
	}
}

/**
 * Executes commands from token chain
 */
int	executor(t_data *data)
{
	t_exec_bag	*eb;
	t_executor	pt;
	int			fd_m;

	if (exec_data_preparation(data) < 0)
		return (-1);
	eb = malloc(sizeof(t_exec_bag));
	if (eb == NULL)
		perror("unable allocate memory");
	pt = ft_init_exec(data);
	init_exec_bag(eb, data, &pt);
	fd_m = STDIN_FILENO;
	iterate_commands(eb, data);
	pt.comm = data->exec->cmd;
	pt.append = data->exec->append;
	if (eb->run)
		eb->e_c = ft_loop(&pt, fd_m);
	free_alloc(&pt);
	data->exec->infile = NULL;
	return (eb->e_c);
}
