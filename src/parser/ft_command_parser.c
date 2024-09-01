/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_parser.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:17:25 by voparkan          #+#    #+#             */
/*   Updated: 2024/09/01 21:12:26 by voparkan         ###   ########.fr       */
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

void trim_all(char **splitcmd)
{
	int	i;

	i = 0;
	while (splitcmd[i])
	{
		printf("before trim: |%s|\n", splitcmd[i]);
		cmd_space_trim(splitcmd[i]);
		printf("after trim: |%s|\n", splitcmd[i]);
		i++;
	}
}

int	get_command_array(t_lex_cmd *lex_cmd, t_bagp *psr, t_data *data) {
	int i;
	char **prepare;

	i = 0;
	prepare = NULL;
	printf("start of get command array, dlmtr: %c\n", lex_cmd->dlmtr);
	if (ft_strrchr(lex_cmd->cmd, (int)lex_cmd->dlmtr))
	{
		printf("get command array if\n");
		if (lex_cmd->dlmtr == '>' || lex_cmd->dlmtr == '<') {
			prepare = ft_split(lex_cmd->cmd, lex_cmd->dlmtr);
			lex_cmd->cmd = prepare[0];
			lex_cmd->dlmtr = ' ';
		}
		psr->splitcmd = ft_split(lex_cmd->cmd, lex_cmd->dlmtr);
		if (psr->splitcmd[0])
		{
			if (lex_cmd->dlmtr != '"' && lex_cmd->dlmtr != '\'')
				trim_all(psr->splitcmd);
			else
				cmd_space_trim(psr->splitcmd[i]);
			printf("splitcmd[1] %s\n", psr->splitcmd[1]);
			if (!check_cmd_path_exists(psr->splitcmd[i], data)) {
				perror(psr->splitcmd[0]);
				return (-1);
			}
			psr->pathcmd = get_cmd_path(psr->splitcmd[i], data);
			psr->combined = ft_strjoin(ft_strjoin(psr->pathcmd, "\x15"), \
			psr->splitcmd[i]);
			i += 1;
			while (psr->splitcmd[i]) // i + 1 solves outfile
 			{
				psr->combined = ft_strjoin(ft_strjoin(psr->combined, "\x15"), \
				psr->splitcmd[i]);
				i++;
			}
			psr->array = ft_split(psr->combined, '\x15');
		}
	}
	else
	{
		printf("get command array else\n");
		cmd_space_trim(lex_cmd->cmd);
		printf("debug %s\n", lex_cmd->cmd);
		if (!check_cmd_path_exists(lex_cmd->cmd, data)) {
			perror(lex_cmd->cmd);
			return (-1);
		}
		psr->pathcmd = get_cmd_path(lex_cmd->cmd, data);
		psr->combined = ft_strjoin(psr->pathcmd, ft_strjoin("\x15", lex_cmd->cmd));
		psr->array = ft_split(psr->combined, '\x15');
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
	int		i;

	i = 0;
	command = parse_argv(argv, pt, data);
	if (!pt->parsing_ok)
		return (-1);
	if (command && command[0])
		ft_lstadd_back(&pt->comm, ft_lstnew((void **) command));
	pt->c_pi = count_pipes(pt);
	if (pt->c_pi > 0)
	{
		pt->pid = (int *)malloc((pt->c_pi + 1) * sizeof(int));
		while (i < pt->c_pi)
		{
			pt->pid[i] = -1;
			i++;
		}
	}
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
