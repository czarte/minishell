/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by voparkan          #+#    #+#             */
/*   Updated: 2024/08/06 16:43:14 by smelicha         ###   ########.fr       */
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

void	check_commands(t_executor *pt)
{
	t_list	*temp;
	char	**con;

	temp = pt->comm;
	while (pt->comm)
	{
		printf("-----------\n");
		con = (char **) pt->comm->content;
		while (*con)
		{
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

void	print_token_chain(t_data *data)
{
	t_token_chain	*current;

	current = data->token_chain->next;
	while (current)
	{
		if (data->debug)
		{
			printf("token: %s\ttype: %s\n", current->token, current->type);
			printf("\n");
		}
		current = current->next;
	}
}
