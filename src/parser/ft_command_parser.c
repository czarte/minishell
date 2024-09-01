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
	t_bagp		psr;
	t_lex_cmd	*lex_cmd;

	psr.pipes = NULL;
	printf("strrchr %s\n", ft_strrchr(arg, (int) '|'));
	if (ft_strrchr(arg, (int) '|'))
		psr.pipes = ft_split(arg, '|');
	if (psr.pipes)
	{
		while (*psr.pipes)
		{
			lex_cmd = lexer(*psr.pipes, data, pt);
			printf("pipes returned pointer %p\n", lex_cmd);
			if (lex_cmd == NULL)
				return (NULL);
			if (get_command_array(lex_cmd, &psr, data) < 0)
				return (NULL);
			free(lex_cmd);
			if (psr.array[0])
				ft_lstadd_back(&pt->comm, ft_lstnew((void **) psr.array));
			psr.pipes++;
		}
		printf("from parse argv\n");
		check_commands(pt);
		pt->parsing_ok = false;
		psr.array = NULL;
	}
	else
	{
		lex_cmd = lexer(arg, data, pt);
		printf("nopipes returned pointer %p\n", lex_cmd);
		if (lex_cmd == NULL)
				return (NULL);
		if (get_command_array(lex_cmd, &psr, data) < 0)
			return (NULL);
		free(lex_cmd);
	}
	pt->parsing_ok = true;
	return (psr.array);
}

int	get_command_array(t_lex_cmd *lex_cmd, t_bagp *psr, t_data *data) {
	printf("start of get command array\n");
	if (ft_strrchr(lex_cmd->cmd, (int)lex_cmd->dlmtr))
	{
		psr->splitcmd = ft_split(lex_cmd->cmd, lex_cmd->dlmtr);
		if (psr->splitcmd[0])
		{
			cmd_space_trim(psr->splitcmd[0]);
			if (!check_cmd_path_exists(psr->splitcmd[0], data)) {
				perror(psr->splitcmd[0]);
				return (-1);
			}
			psr->pathcmd = get_cmd_path(psr->splitcmd[0], data);
			psr->combined = ft_strjoin(ft_strjoin(psr->pathcmd, " "), \
		lex_cmd->cmd);
			psr->array = ft_split(psr->combined, ' ');
		}
	}
	else
	{
		cmd_space_trim(lex_cmd->cmd);
		printf("debug %s\n", lex_cmd->cmd);
		if (!check_cmd_path_exists(lex_cmd->cmd, data)) {
			perror(lex_cmd->cmd);
			return (-1);
		}
		psr->pathcmd = get_cmd_path(lex_cmd->cmd, data);
		psr->combined = ft_strjoin(psr->pathcmd, ft_strjoin(" ", lex_cmd->cmd));
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

	return (0);
}

int	parse_path(t_executor *pt, char *argv, t_data *data)
{
	char	**command;

	command = parse_argv(argv, pt, data);
	if (!pt->parsing_ok)
	{
		perror("Something went wrong");
		return (-1);
	}
	if (command && command[0])
		ft_lstadd_back(&pt->comm, ft_lstnew((void **) command));
	return (0);
}

int	ft_parse_command(t_executor *pt, char *argv, t_data *data)
{
	if (parse_path(pt, argv, data) < 0)
		return (0);
	check_commands(pt);
	print_t_executor(pt);
	return (check_commands(pt));
}
