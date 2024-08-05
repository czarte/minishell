/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: voparkan <voparkan@student.42prague.cz>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 20:04:38 by voparkan          #+#    #+#             */
/*   Updated: 2024/08/04 17:57:30 by voparkan         ###   ########.fr       */
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

typedef struct s_exec_bag
{
	t_token_chain	*cur;
	bool			run;
	int				e_c;
} t_exec_bag;

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
}


void	init_exec_bag(t_exec_bag *eb, t_data *data, t_executor *pt)
{
	eb->run = false;
	eb->e_c = 0;
	eb->cur = NULL;
	eb->cur = data->token_chain->next;
	assign_pt(data, pt);
}

void	iterate_commands(t_exec_bag *eb, t_data *data)
{
	while (eb->cur)
	{
		if (str_comp(eb->cur->type, "bu"))
			execute_builtin(eb->cur, data);
		else if (str_comp(eb->cur->type, "vd"))
			envp_add_reallocate(data, eb->cur->token, 1);
		else if (str_comp(eb->cur->type, "pr")) {
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
	if (eb < 0)
		perror("unable allocate memory");
	pt = ft_init_exec(0, NULL, data);
	init_exec_bag(eb, data, &pt);
	fd_m = STDIN_FILENO;
	iterate_commands(eb, data);
	pt.comm = data->exec->cmd;
	if (data->exec->append)
		pt.append = true;
	if (eb->run)
		eb->e_c = ft_loop(&pt, fd_m);
	free_alloc(&pt);
	data->exec->infile = NULL;
	return (eb->e_c);
}
