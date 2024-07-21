/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_parser.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:17:25 by voparkan          #+#    #+#             */
/*   Updated: 2024/07/19 18:33:17 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"
#include "../../incl/executor.h"

void	ft_check_access(char *pathcmd, char ***array)
{
	if (access(pathcmd, F_OK) == -1)
	{
		*array = malloc(1 * sizeof (char *));
		*array[0] = NULL;
	}
}

char	**parse_argv(char *arg, t_executor *pt)
{
	t_bagp	psr;

	if (ft_strrchr(arg, (int) ' '))
	{
		psr.splitcmd = ft_split(arg, ' ');
		if (psr.splitcmd[0])
		{
			psr.pathcmd = ft_strjoin(*pt->path, ft_strjoin("/", \
			psr.splitcmd[0]));
			psr.combined = ft_strjoin(ft_strjoin(psr.pathcmd, " "), \
			arg);
			psr.array = ft_split(psr.combined, ' ');
		}
	}
	else
	{
		psr.pathcmd = ft_strjoin(*pt->path, ft_strjoin("/", arg));
		psr.combined = ft_strjoin(psr.pathcmd, ft_strjoin(" ", arg));
		psr.array = ft_split(psr.combined, ' ');
	}
	ft_check_access(psr.pathcmd, &psr.array);
	return (psr.array);
}

//void	check_commands(t_executor *pt)
//{
//	t_list	*temp;
//	int		end;
//
//	temp = pt->comm;
//	end = 1;
//	while (pt->comm)
//	{
//		if (access(pt->comm->content[0], X_OK == -1))
//			printf("minishell: command not found: %s\n", (char *)
//					pt->comm->content[0]);
//		pt->comm = pt->comm->next;
//	}
//	pt->comm = temp;
//}

void	parse_path(t_executor *pt, int *flag, char **argv, char **tmp)
{
	char	**command;

	while (*pt->path)
	{
		command = parse_argv(argv[pt->it], pt);
		if (command[0])
		{
			ft_lstadd_back(&pt->comm, ft_lstnew((void *) command));
			pt->path = tmp;
			*flag = 1;
			break ;
		}
		else
			pt->path++;
	}
}

int	ft_parse_command(t_executor *pt, int argc, char **argv)
{
	int		flag;
	char	**command;
	char	**tmp;

	pt->it = 2;
	tmp = pt->path;
	while (pt->it < (argc - 1))
	{
		flag = 0;
		parse_path(pt, &flag, argv, tmp);
		if (!flag)
		{
			command = ft_split(ft_strjoin(ft_strjoin(argv[pt->it], " "),
						argv[pt->it]), ' ');
			ft_lstadd_back(&pt->comm, ft_lstnew((void *) command));
			pt->path = tmp;
		}
		pt->it++;
	}
	check_commands(pt);
	return (0);
}
