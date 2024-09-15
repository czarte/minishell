/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_array_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: voparkan <voparkan@student.42prague.cz>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:35:35 by voparkan          #+#    #+#             */
/*   Updated: 2024/09/15 20:41:36 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"
#include "../../incl/executor.h"

char	**granulate_command(t_bagp *psr, const t_data *data, char **tmp)
{
	int		i;
	char	*tempsplit;
	size_t	cnt;

	i = 0;
	if (data->debug)
		printf("count_splited: %d, i: %d\n", count_splited(psr->splitcmd), i);
	tmp = malloc((count_splited(psr->splitcmd) + 1) * sizeof(char *));
	add_to_collection((void *)tmp, psr->pt);
	while (psr->splitcmd[++i])
		tmp[i - 1] = psr->splitcmd[i];
	tmp[i - 1] = NULL;
	tempsplit = ft_memdup(psr->splitcmd[0]);
	add_to_collection((void *)tempsplit, psr->pt);
	cnt = ft_count_tokens(tempsplit, ' ');
	psr->splitcmd = ft_split(tempsplit, ' ');
	add_array_to_collection((void *)psr->splitcmd, psr->pt);
	psr->splitcmd[cnt] = NULL;
	return (tmp);
}

void	prepare_piped_array(t_lex_cmd *lex_cmd, t_bagp *psr, const t_data *data,
	char **prepare)
{
	char	**tmpsc;

	if (data->debug)
		printf("get command array if\n");
	if (lex_cmd->dlmtr == '>' || lex_cmd->dlmtr == '<')
	{
		prepare = ft_split(lex_cmd->cmd, lex_cmd->dlmtr);
		add_array_to_collection((void **)prepare, psr->pt);
		lex_cmd->cmd = prepare[0];
		lex_cmd->dlmtr = ' ';
	}
	psr->splitcmd = ft_split(lex_cmd->cmd, lex_cmd->dlmtr);
	add_array_to_collection((void **)psr->splitcmd, psr->pt);
	tmpsc = psr->splitcmd;
	if (data->debug && tmpsc)
	{
		while (*tmpsc)
		{
			printf("psr splitcmd: %s\n", *tmpsc);
			tmpsc++;
		}
	}
}

int	create_array(t_lex_cmd *lex_cmd, t_bagp *psr, t_data *data, char **tmp)
{
	int		i;
	char	*temp;

	i = 0;
	if (psr->splitcmd[0])
	{
		if (lex_cmd->dlmtr != '"' && lex_cmd->dlmtr != '\'')
			trim_all(psr->splitcmd);
		else
			cmd_trim(psr->splitcmd[i], ' ');
		if (data->debug)
			printf("splitcmd[1] %s\n", psr->splitcmd[1]);
		if (!check_cmd_path_exists(psr->splitcmd[0], data))
		{
			perror(psr->splitcmd[0]);
			return (-1);
		}
		psr->pathcmd = get_cmd_path(psr->splitcmd[0], data);
		add_to_collection((void *)psr->pathcmd, psr->pt);
		temp = ft_strjoin(psr->pathcmd, "\x15");
		add_to_collection((void *)temp, psr->pt);
		psr->combined = ft_strjoin(temp, psr->splitcmd[0]);
		add_to_collection((void *)psr->combined, psr->pt);
//		free(temp);
		appedn_command_bits(psr, tmp, data);
		psr->array = ft_split(psr->combined, '\x15');
		add_array_to_collection((void **)psr->array, psr->pt);
	}
	return (0);
}

int	get_simple_cmd_array(t_lex_cmd *lex_cmd, t_bagp *psr, t_data *data)
{
	char *partial;

	partial = NULL;
	cmd_trim(lex_cmd->cmd, ' ');
	if (data->debug)
		printf("debug %s\n", lex_cmd->cmd);
	if (!check_cmd_path_exists(lex_cmd->cmd, data))
	{
		errno = EINVAL;
		perror("Command not found");
		g_last_status = 127;
		return (-1);
	}
	psr->pathcmd = get_cmd_path(lex_cmd->cmd, data);
	add_to_collection((void *)psr->pathcmd, psr->pt);
	partial = ft_strjoin("\x15", lex_cmd->cmd);
	add_to_collection((void *)partial, psr->pt);
	psr->combined = ft_strjoin(psr->pathcmd, partial);
	add_to_collection((void *)psr->combined, psr->pt);
	psr->array = ft_split(psr->combined, '\x15');
	add_array_to_collection((void **)psr->array, psr->pt);
//	free(partial);
//	free(psr->combined);
	return (0);
}

void	appedn_command_bits(t_bagp *psr, char **tmp, t_data *data)
{
	int		i;
	char	*temp;

	i = 1;
	temp = NULL;
	while (psr->splitcmd[i])
	{
		if (str_comp(psr->splitcmd[i], ">") || str_comp(psr->splitcmd[i], ">>"))
			break;
		if (data->debug)
			printf("splitcmd[i]: %s\n", psr->splitcmd[i]);
		temp = ft_strjoin(psr->combined, "\x15");
		add_to_collection((void *)temp, psr->pt);
		psr->combined = ft_strjoin(temp, \
				psr->splitcmd[i]);
		add_to_collection((void *)psr->combined, psr->pt);
		i++;
	}
	i = 0;
	if (tmp)
	{
		while (tmp[i])
		{
			temp = ft_strjoin(psr->combined, "\x15");
			add_to_collection((void *)temp, psr->pt);
			psr->combined = ft_strjoin(temp, tmp[i]);
			add_to_collection((void *)psr->combined, psr->pt);
			i++;
		}
	}
}
