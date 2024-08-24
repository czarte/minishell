/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_parser.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:17:25 by voparkan          #+#    #+#             */
/*   Updated: 2024/08/24 14:24:18 by voparkan         ###   ########.fr       */
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

char	**parse_argv(char *arg, t_executor *pt, t_data *data)
{
	t_bagp	psr;

	psr.pipes = NULL;
	printf("strrchr %s\n", ft_strrchr(arg, (int) '|'));
	if (ft_strrchr(arg, (int) '|'))
		psr.pipes = ft_split(arg, '|');
	if (psr.pipes)
	{
		while (*psr.pipes)
		{
			printf("psr.pipes %s\n", *psr.pipes);
			get_command_array(*psr.pipes, &psr, data);
			if (psr.array[0])
				ft_lstadd_back(&pt->comm, ft_lstnew((void **) psr.array));
			psr.pipes++;
		}
		check_commands(pt);
		psr.array = NULL;
	}
	else
	{
		get_command_array(arg, &psr, data);
	}

	return (psr.array);
}

void	get_command_array(const char *arg, t_bagp *psr, t_data *data) {
	if (ft_strrchr(arg, (int) ' '))
	{
		psr->splitcmd = ft_split(arg, ' ');
		if (psr->splitcmd[0])
		{
			if (!check_cmd_path_exists(psr->splitcmd[0], data)) {
				perror(psr->splitcmd[0]);
				return ;
			}
			psr->pathcmd = get_cmd_path(psr->splitcmd[0], data);
			psr->combined = ft_strjoin(ft_strjoin(psr->pathcmd, " "), \
		arg);
			psr->array = ft_split(psr->combined, ' ');
		}
	}
	else
	{
		printf("debug %s\n", arg);
		if (!check_cmd_path_exists(arg, data)) {
			perror(arg);
			return ;
		}
		psr->pathcmd = get_cmd_path(arg, data);
		psr->combined = ft_strjoin(psr->pathcmd, ft_strjoin(" ", arg));
		psr->array = ft_split(psr->combined, ' ');
	}

	ft_check_access((*psr).pathcmd, &(*psr).array);
	printf("psr pathcmd: %s\n", psr->pathcmd);
	printf("psr combined: %s\n", psr->combined);
	char **tmp = psr->array;
	if (tmp) {
		while (*tmp) {
			printf("psr array: %s\n", *tmp);
			tmp++;
		}
	}
}

void	parse_path(t_executor *pt, char *argv, t_data *data)
{
	char	**command;

	command = parse_argv(argv, pt, data);
	if (command && command[0])
		ft_lstadd_back(&pt->comm, ft_lstnew((void **) command));
}

int	ft_parse_command(t_executor *pt, char *argv, t_data *data)
{
	parse_path(pt, argv, data);
	check_commands(pt);
	return (check_commands(pt));
}
