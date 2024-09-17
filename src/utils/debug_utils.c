/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by voparkan          #+#    #+#             */
/*   Updated: 2024/09/17 18:02:45 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"
#include "../../incl/executor.h"

void	print_exec_data(t_exec *exec)
{
	t_list	*current;

	current = exec->cmd;
	printf("Cmd list:\n");
	if (current)
	{
		while (*current->content)
		{
			printf("%s\n", (char *) *current->content);
			current->content++;
		}
		current = current->next;
	}
	if (exec->infile)
		printf("infile: %s\n", (char *)exec->infile);
	if (exec->outfile)
		printf("file[1]: %s\n", (char *)exec->outfile);
	if (exec->limit)
		printf("Exec limit true\n");
	else
		printf("Exec limit false\n");
	if (exec->append)
		printf("Exec append true\n");
	else
		printf("Execl append false\n");
}

void	print_t_executor_print_array(char **arr)
{
	while (*arr)
	{
		printf("%s\n", *arr);
		arr++;
	}
}

void	print_t_executor(t_executor *pt)
{
	t_list	*ltmp;

	if (pt->debug) {
		ltmp = pt->comm;
		printf("\n====    PT    ====\n");
		printf("debug:\t%i\n", pt->debug);
		printf("heredoc:\t%i\n", pt->heredoc);
		printf("heredoc_rl:\t%i\n", pt->heredoc_rl);
		printf("append:\t%i\n", pt->append);
		printf("c_pi:\t%i\n", pt->c_pi);
		printf("file_fd[0]:\t%i\nfile_fd[1]: %i\n", pt->filefd[0],
			   pt->filefd[1]);
		printf("it:\t%i\n", pt->it);
		printf("end:\t%i\n", pt->end);
		printf("fsucc:\t%i\n", pt->fsucc);
		printf("status:\t%i\n", pt->status);
		printf("psucc:\t%i\n", pt->psucc);
		if (pt->pid)
			printf("pid:\t%i\n", *pt->pid);
		else
			printf("pid:\rNULL\n");
		if (pt->pwd)
			printf("pwd:\t%s\n", pt->pwd);
		else
			printf("pwd:\tNULL\n");
		if (pt->home)
			printf("home:\t%s\n", pt->home);
		else
			printf("home:\tNULL\n");
		if (ltmp) {
			printf("comm:\n");
			while (ltmp) {
				print_t_executor_print_array((char **) ltmp->content);
				ltmp = ltmp->next;
			}
		} else
			printf("comm:\tNULL\n");
		if (pt->argv) {
			printf("argv:\n");
			print_t_executor_print_array(pt->argv);
		} else
			printf("argv:\tNULL\n");
		if (pt->path) {
			printf("path:\n");
			print_t_executor_print_array(pt->path);
		} else
			printf("path:\tNULL\n");
		if (pt->infile)
			printf("infile:\t%s\n", pt->infile);
		else
			printf("infile:\tNULL\n");
		if (pt->outfile)
			printf("outfile:\t%s\n", pt->outfile);
		else
			printf("outfile:\tNULL\n");
		if (pt->dlmtr)
			printf("dlmtr:\t%s\n", pt->dlmtr);
		else
			printf("dlmtr\tNULL\n");
		printf("========\n\n");
	}
}

int	check_commands(t_executor *pt)
{
	t_list	*temp;
	char	**con;
	int 	n;

	temp = pt->comm;
	while (temp)
	{
		if (pt->debug)
			printf("------check commands-----\n");
		con = (char **) temp->content;
		n = 0;
		while (*con)
		{
			if (n > 0 && *con)
			{
//				printf("con: %s, n: %d\n", *con, n);
				//cmd_trim(*con, ' ');
				if (*con[0] == '\'' && *con[ft_strlen(*con) - 1] == '\'')
					cmd_trim(*con, '\'');
				if (*con[0] == '"' && *con[ft_strlen(*con) - 1] == '"')
					cmd_trim(*con, '"');
			}
			if (pt->debug)
				printf("command: |%s|\n",*con);
			con++;
			n++;
		}
		if (access(temp->content[0], X_OK == -1) && !str_comp(temp->content[0], "builtin"))
		{
			pt->parsing_ok = false;
			ft_putstr_fd("minishell: command not found:\n", STDERR_FILENO);
		}
		temp = temp->next;
	}
	if (pt->debug)
		printf("return from check commands: %d\n", n);
	return (ft_lstsize(pt->comm));
}

void	print_token_chain(t_data *data)
{
	t_token_chain	*current;

	current = data->token_chain->next;
	while (current)
	{
		if (data->debug)
		{
			printf("token: %s\ttype: %s", current->token, current->type);
			printf("\n");
		}
		current = current->next;
	}
}
