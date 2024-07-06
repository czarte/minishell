/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: voparkan <voparkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:51:04 by stepan            #+#    #+#             */
/*   Updated: 2024/07/06 18:11:21 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"
#include "../../incl/executor.h"

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
	return (0);
}

/**
 * Executes commands from token chain
 */
int	executor(t_data *data)
{
	t_token_chain	*current;
	t_executor 		pt;

	current = data->token_chain->next;
	while (current)
	{
		if (str_comp(current->type, "bu"))
			execute_builtin(current, data);
		else if (str_comp(current->type, "vd"))
			envp_add_reallocate(data, current->token, 1);
		else if (str_comp(current->type, "pr")) {
			char **command = malloc(tokens_len(current) * sizeof (char *));
			while (tokens_len(current))
			command[0] = current->token;
			command[1] = get_cmd_path(current->token, data);
			if (str_comp(current->next->type, "ar"))
				command[2] = current->next->token;
			else
				command[2] = NULL;
			command[3] = NULL;
			pt = ft_init_exec(0, &data->cmd_list->cmd, data->envp);
			ft_loop(&pt);
			wait_subprocess(&pt);
		}
		current = current->next;
	}
	return (0);
}
