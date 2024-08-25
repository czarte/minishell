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

void	*prepare_lexer_data(char *cmd, t_data *data)
{
	t_lex_cmd	*lex_data;

	lex_data = malloc(sizeof(t_lex_cmd));
	if (!lex_data)
	{
		perror("Lexer list allocation");
		return (NULL);
	}
	lex_data->cmd = cmd;
	lex_data->dlmtr = '\0';
	lex_data->split = false;
	ft_lstadd_back(&data->lexer_list, (void *)ft_lstnew(lex_data));
	return (0);
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
			lex_cmd = lexer(*psr.pipes, data);
			if (lex_cmd == NULL)
				return (NULL);
			get_command_array(lex_cmd, &psr, data);
			free(lex_cmd);
			if (psr.array[0])
				ft_lstadd_back(&pt->comm, ft_lstnew((void **) psr.array));
			psr.pipes++;
		}
		check_commands(pt);
		psr.array = NULL;
	}
	else
	{
		lex_cmd = lexer(arg, data);
		if (lex_cmd == NULL)
				return (NULL);
		get_command_array(lex_cmd, &psr, data);
		free(lex_cmd);
	}
	return (psr.array);
}

void	get_command_array(t_lex_cmd *lex_cmd, t_bagp *psr, t_data *data) {
	if (ft_strrchr(lex_cmd->cmd, (int)lex_cmd->dlmtr))
	{
		psr->splitcmd = ft_split(lex_cmd->cmd, lex_cmd->dlmtr);
		if (psr->splitcmd[0])
		{
			if (!check_cmd_path_exists(psr->splitcmd[0], data)) {
				perror(psr->splitcmd[0]);
				return ;
			}
			psr->pathcmd = get_cmd_path(psr->splitcmd[0], data);
			psr->combined = ft_strjoin(ft_strjoin(psr->pathcmd, " "), \
		lex_cmd->cmd);
			psr->array = ft_split(psr->combined, ' ');
		}
	}
	else
	{
		printf("debug %s\n", lex_cmd->cmd);
		if (!check_cmd_path_exists(lex_cmd->cmd, data)) {
			perror(lex_cmd->cmd);
			return ;
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
}

void	parse_path(t_executor *pt, char *argv, t_data *data)
{
	char	**command;

	command = parse_argv(argv, pt, data);
	if (command == NULL)
	{
		perror("Something went wrong");
		return ;
	}
	if (command && command[0])
		ft_lstadd_back(&pt->comm, ft_lstnew((void **) command));
}

int	ft_parse_command(t_executor *pt, char *argv, t_data *data)
{
	parse_path(pt, argv, data);
	check_commands(pt);
	return (check_commands(pt));
}
