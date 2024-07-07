/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:51:04 by stepan            #+#    #+#             */
/*   Updated: 2024/07/07 16:22:06 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"
#include "../../incl/executor.h"

void	print_exec_data(t_exec *exec)
{
	t_list	*current = exec->cmd;
	printf("Cmd list:\n");
	if (current)
	{
		while (*current->content)
		{
			printf("%s\n", (char*)*(*current).content);
			current->content++;
		}
		current = current->next;
	}
	printf("file[0]: %s\n", (char*)exec->file[0]);
	printf("file[1]: %s\n", (char*)exec->file[1]);
	if (exec->limit)
		printf("Exec limit true\n");
	else
		printf("Exec limit false\n");
	if (exec->append)
		printf("Exec append true\n");
	else
		printf("Execl append false\n");
}

int	command_arg_count(t_token_chain *tc)
{
	int				i;
	t_token_chain	*current;

	if (tc->next)
		current = tc->next;
	else
		return (0);
	i = 0;
	while (current && str_comp(current->type, "ar"))
	{
		i++;
		current = current->next;
	}
	return (i);
}

int	exec_data_preparation(t_data *data)
{
	t_token_chain	*tc;
	char			**cmd;
	int				arg_count;
	int				i;

	if (exec_data_init(data) < 0)
		return (-1);
	tc = data->token_chain->next;
	i = 2;
	while (tc)
	{
		if (str_comp(tc->type, "pr") || str_comp(tc->type, "bu"))
		{
			arg_count = command_arg_count(tc);
			cmd = malloc(sizeof(char *) * (arg_count + 3));
			cmd[arg_count + 2] = NULL;
			cmd[0] = get_cmd_path(tc->token, data);
			cmd[1] = ft_memcpy(tc->token);
			tc = tc->next;
			while (tc && str_comp(tc->type, "ar"))
			{
				cmd[i] = ft_memcpy(tc->token);
				if (tc->next && str_comp(tc->next->type, "ar"))
					tc = tc->next;
				else
					break ;
			}
			ft_lstadd_back(&data->exec->cmd, ft_lstnew((void*)cmd));
			// printf("arg count: %i\n", arg_count);
		}
		if (tc)
			tc = tc->next;
		if (tc && str_comp(tc->type, "ra"))
			data->exec->append = true;
		if (tc && str_comp(tc->type, "rd"))
			data->exec->limit = true;
	}
	return (0);
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
	return (0);
}

/**
 * Executes commands from token chain
 */
int	executor(t_data *data)
{
	t_token_chain	*current;
	t_executor 		pt;

	if (exec_data_preparation(data) < 0)
		return (-1);
	print_exec_data(data->exec);
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
	free_exec(data);
	return (0);
}
