/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_parser.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:17:25 by voparkan          #+#    #+#             */
/*   Updated: 2024/09/17 21:40:30 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"
#include "../../incl/executor.h"

char	**parse_argv(char *arg, t_executor *pt, t_data *data)
{
	t_bagp		psr;

	psr.pipes = NULL;
	psr.splitcmd = NULL;
	psr.pt = pt;
	psr.pathcmd = NULL;
	if (data->debug)
		printf("strrchr %s\n", ft_skip_quote_strrchr(arg, (int) '|'));
	if (ft_skip_quote_strrchr(arg, (int) '|'))
	{
		psr.pipes = ft_skip_quote_split(arg, '|');
		add_array_to_collection((void **)psr.pipes, pt);
	}
	if (psr.pipes)
	{
		if (iterate_splited(pt, data, &psr) < 0)
			return (NULL);
		if (data->debug)
			printf("from parse argv\n");
		check_commands(pt);
		pt->parsing_ok = true;
		return (psr.array = NULL, psr.array);
	}
	else
		if (extract_simple(arg, pt, data, &psr) < 0)
			return  (psr.array = NULL, psr.array);
	pt->parsing_ok = true;
//	if (psr.splitcmd)
//		free(psr.splitcmd);
	return (psr.array);
}

int	extract_simple(char *arg, t_executor *pt, t_data *data, t_bagp *psr)
{
	t_lex_cmd	*lex_cmd;

	lex_cmd = lexer(arg, data, pt);
	if (lex_cmd == NULL || !ft_strlen(lex_cmd->cmd))
		return (-1);
	if (lex_cmd)
	{
		add_to_collection((void *)lex_cmd->cmd, pt);
		add_to_collection((void *)lex_cmd, pt);
	}
	if (data->debug)
		printf("nopipes returned pointer %p\n", lex_cmd);
	if (lex_cmd == NULL || get_command_array(lex_cmd, psr, data) < 0)
	{
		pt->parsing_ok = false;
		return (-1);
	}
//	free(lex_cmd->cmd);
//	free(lex_cmd);
	return (0);
}

int	get_command_array(t_lex_cmd *lex_cmd, t_bagp *psr, t_data *data)
{
	char	**prepare;
	char	**tmp;

	prepare = NULL;
	tmp = NULL;
	if (data->debug)
		printf("start of get command array, dlmtr: %c\n", lex_cmd->dlmtr);
	if (lex_cmd->dlmtr && ft_strrchr(lex_cmd->cmd, (int)lex_cmd->dlmtr))
	{
		prepare_piped_array(lex_cmd, psr, data, prepare);
		if (ft_count_tokens(psr->splitcmd[0], ' ') > 1)
		{
			tmp = granulate_command(psr, data, tmp);
		}
		if (data->debug)
			print_debug_tmp_split(psr->splitcmd, tmp);
		create_array(lex_cmd, psr, data, tmp);
	}
	else
		if (get_simple_cmd_array(lex_cmd, psr, data) < 0)
			return (-1);
	ft_check_access(psr->pathcmd, &psr->array, psr->pt);
	if (data->debug)
		printf("psr: %p psr->array: %p\n", psr, psr->array);
	if (!*psr->array)
	{
		add_array_to_collection((void **)psr->array, psr->pt);
		return (-1);
	}
//	free(psr->pathcmd);
	if (data->debug)
		print_debug_array(psr);
	return (0);
}

int	parse_path(t_executor *pt, char *argv, t_data *data)
{
	char	**command;
	int		i;

	i = 0;
	command = parse_argv(argv, pt, data);
	if (!pt->parsing_ok || data->parse_fail)
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
	{
		executor_finished_clean(pt, data);
		return (0);
	}
	//print_t_executor(pt);
	return (check_commands(pt));
}
