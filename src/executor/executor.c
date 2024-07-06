/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: voparkan <voparkan@student.42prague.cz>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 20:04:38 by voparkan          #+#    #+#             */
/*   Updated: 2024/07/06 21:38:47 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:51:04 by stepan            #+#    #+#             */
/*   Updated: 2024/07/06 18:57:40 by smelicha         ###   ########.fr       */
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

void	check_commands(t_executor *pt)
{
	t_list	*temp;

	temp = pt->comm;
	while (pt->comm)
	{
		printf("-----------\n");
		char **con = (char **) pt->comm->content;
		while (*con) {
			printf("command: %s\n",*con);
			con++;
		}
		printf("-----------\n");
		if (access(pt->comm->content[0], X_OK == -1))
			printf("minishell: command not found: %s\n", (char *)
					pt->comm->content[0]);
		pt->comm = pt->comm->next;
	}
	pt->comm = temp;
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
			printf("debug: %d", tokens_len(current));
			char **command = malloc((tokens_len(current) + 2)* sizeof (char *));
			//while (tokens_len(current))
			command[0] = get_cmd_path(current->token, data);
			command[1] = current->token;
			if (current->next && str_comp(current->next->type, "ar"))
				command[2] = current->next->token;
			else
				command[2] = NULL;
			command[3] = NULL;
			pt = ft_init_exec(0, NULL, data->envp);
			ft_lstadd_back(&pt.comm, ft_lstnew((void *) command));
		}
		current = current->next;
	}
	check_commands(&pt);
	ft_loop(&pt);
	wait_subprocess(&pt);
	return (0);
}
