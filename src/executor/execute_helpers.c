/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by voparkan          #+#    #+#             */
/*   Updated: 2024/09/03 09:53:45 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"
#include "../../incl/executor.h"

void	assign_pt(t_data *data, t_executor *pt)
{
	if (data->exec->infile)
	{
		pt->infile = data->exec->infile;
		data->exec->infile = NULL;
		pt->heredoc = true;
	}
	else
		pt->infile = NULL;
	if (data->exec->outfile)
	{
		pt->outfile = data->exec->outfile;
		data->exec->outfile = NULL;
	}
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

void	init_exec_bag(t_exec_bag *eb, t_data *data, t_executor *pt)
{
	eb->run = false;
	eb->cur = NULL;
	eb->cur = data->token_chain->next;
	assign_pt(data, pt);
}

int	command_arg_count(t_token_chain *tc, t_data *data)
{
	int				i;
	t_token_chain	*current;

	if (tc->next)
		current = tc->next;
	else
		return (0);
	i = 0;
	while (str_comp(current->type, "ar"))
	{
		i++;
		if (current->next && str_comp(current->next->type, "ar"))
			current = current->next;
		else
			break ;
	}
	if (data->debug)
		printf("arg count: %d\n", i);
	return (i);
}

/**
 * Finds out which of the builtin commands to execute
 */
int	execute_builtin(void **current, t_data *data)
{
	if (str_comp(current[1], "cd"))
		cd((char *) current[2], data);
	else if (str_comp(current[1], "pwd"))
		printf("%s\n", data->work_dir);
	else if (str_comp(current[1], "echo"))
		echo((char **) current);
	else if (str_comp(current[1], "env"))
		env(data);
	else if (str_comp(current[1], "export"))
		write(1, "TODO fix export\n", 16); //b_export(current[1], data);
	else if (str_comp(current[1], "unset"))
		write(1, "TODO fix unset\n", 15); //unset(current, data);
	else if (str_comp(current[1], "help"))
		help();
	return (0);
}
