/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 17:05:30 by smelicha          #+#    #+#             */
/*   Updated: 2024/11/14 09:20:59 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

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

int	check_commands_trim_cont(char **con, t_executor *pt)
{
	int		n;

	n = 0;
	while (*con)
	{
		if (n > 0 && *con)
		{
			if (ft_strlen(*con) == 2 && ((**con == '\'' || \
				**con == '"')) && *(*con + ft_strlen(*con) - 1) == **con)
				**con = '\0';
			else if ((**con == '\'' || **con == '"') && \
				*(*con + ft_strlen(*con) - 1) == **con)
				cmd_trim(*con, **con);
			else
				remove_unescaped_quotes(*con);
		}
		if (pt->debug)
			printf("command: |%s|\n",*con);
		con++;
		n++;
	}
	return (n);
}

void	remove_unescaped_quotes(char *con)
{
	int	n;

	n = ft_strlen(con);
	while ((*con + n) > (*con))
	{
		if (n > 0 && (*(con + n) == '"' || *(con + n) == '\''))
		{
			if (*(con + n - 1) == '\\')
			{
				ft_memmove((con + (n - 1)), (con + n),
					ft_strlen((con + n)) + 1);
				n--;
			}
			else
				ft_memmove((con + n), (con + n + 1), ft_strlen((con + n)));
		}
		n--;
	}
}

int	check_commands(t_executor *pt)
{
	t_list	*temp;
	char	**con;
	int		ret;

	temp = pt->comm;
	ret = 0;
	while (temp)
	{
		if (pt->debug)
			printf("------check commands-----\n");
		con = (char **) temp->content;
		ret = check_commands_trim_cont(con, pt);
		if (access(temp->content[0], X_OK == -1) \
			&& !str_comp(temp->content[0], "builtin"))
		{
			pt->parsing_ok = false;
			ft_putstr_fd("minishell: command not found:\n", STDERR_FILENO);
		}
		temp = temp->next;
	}
	if (pt->debug)
		printf("return from check commands: %d\n", ret);
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
