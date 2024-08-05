/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: voparkan <voparkan@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by voparkan          #+#    #+#             */
/*   Updated: 2024/08/05 20:14:24 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"
#include "../../incl/executor.h"

void	init_exec_bag(t_exec_bag *eb, t_data *data, t_executor *pt)
{
	eb->run = false;
	eb->e_c = 0;
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
int	execute_builtin(t_token_chain *current, t_data *data)
{
	if (str_comp(current->token, "cd") && current->next)
		cd(current->next->token, data);
	else if (str_comp(current->token, "pwd"))
		printf("%s\n", data->work_dir);
	else if (str_comp(current->token, "echo"))
		echo(current);
	else if (str_comp(current->token, "env"))
		env(data);
	else if (str_comp(current->token, "export"))
		b_export(current, data);
	else if (str_comp(current->token, "unset"))
		unset(current, data);
	else if (str_comp(current->token, "help"))
		help();
	return (0);
}
