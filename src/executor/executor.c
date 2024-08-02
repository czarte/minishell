/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: voparkan <voparkan@student.42prague.cz>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 20:04:38 by voparkan          #+#    #+#             */
/*   Updated: 2024/08/02 11:51:08 by voparkan         ###   ########.fr       */
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
			printf("%s\n", (char*) *current->content);
			current->content++;
		}
		current = current->next;
	}
	if (exec->infile)
		printf("infile: %s\n", (char*)exec->infile);
	if (exec->outfile)
		printf("file[1]: %s\n", (char*)exec->outfile);
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
	while (str_comp(current->type, "ar"))
	{
		i++;
		if (current->next && str_comp(current->next->type, "ar"))
			current = current->next;
		else
			break;
	}
	printf("arg count: %d\n", i);
	return (i);
}

int	exec_data_preparation(t_data *data)
{
	t_token_chain	*tc;
	char			**cmd;
	int				arg_count;
	int				i;

	tc = data->token_chain->next;
	i = 2;
	while (tc)
	{
		if (tc->next && str_comp(tc->type, "ri")) {
			tc = tc->next;
			continue;
		}
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
				{
					tc = tc->next;
					i++;
				}
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
	else if (str_comp(current->token, "help"))
		help();
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
	bool			run;
	int				exit_code;
	int				fd_m;

	run = false;
	exit_code = 0;
	if (exec_data_preparation(data) < 0)
		return (-1);
	current = data->token_chain->next;
	pt = ft_init_exec(0, NULL, data);
	if (data->exec->infile)
	{
		pt.infile = data->exec->infile;
		pt.heredoc = true;
	}
	else
		pt.infile = NULL;
	if (data->exec->outfile)
		pt.outfile = data->exec->outfile;
	else
		pt.outfile = NULL;
	pt.pwd = getenv("PWD");
	fd_m = STDIN_FILENO;
	while (current)
	{
		if (str_comp(current->type, "bu"))
			execute_builtin(current, data);
		else if (str_comp(current->type, "vd"))
			envp_add_reallocate(data, current->token, 1);
		else if (str_comp(current->type, "pr")) {
			run = true;
			break ;
		}
		current = current->next;
	}
	//print_exec_data(data->exec);
	pt.comm = data->exec->cmd;
	printf("data->exec->infile %s\n", data->exec->infile);
	//printf("heredoc %d\n", pt.heredoc);
	//check_commands(&pt);
	if (run)
		exit_code = ft_loop(&pt, fd_m);
	free_alloc(&pt);
	data->exec->infile = NULL;
	//free_exec(data);
	return (exit_code);
}
