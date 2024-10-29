/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: voparkan <voparkan@student.42prague.cz>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:32:37 by voparkan          #+#    #+#             */
/*   Updated: 2024/09/08 16:50:12 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"
#include "../../incl/executor.h"

void	trim_all(char **splitcmd)
{
	int	i;

	i = 0;
	while (splitcmd[i])
	{
		cmd_trim(splitcmd[i], ' ');
		i++;
	}
}

int	count_splited(char **cmd)
{
	int	i;

	i = 0;
	while (*cmd)
	{
		i++;
		cmd++;
	}
	return (i);
}

void	print_debug_tmp_split(char **splitcmd, char **tmp)
{
	char	**tmpscat;
	char	**tmpsca;

	tmpsca = splitcmd;
	tmpscat = tmp;
	if (tmpsca)
	{
		while (*tmpsca)
		{
			printf("psr splitcmd after tmp: %s\n", *tmpsca);
			tmpsca++;
		}
	}
	if (tmpscat)
	{
		while (*tmpscat)
		{
			printf("psr tmp after tmp: %s\n", *tmpscat);
			tmpscat++;
		}
	}
}

void	print_debug_array(t_bagp *psr)
{
	char	**tmpd;

	tmpd = psr->array;
	if (tmpd)
	{
		while (*tmpd)
		{
			printf("psr array: %s\n", *tmpd);
			tmpd++;
		}
	}
}

int		iterate_splited(t_executor *pt, t_data *data, t_bagp *psr)
{
	t_lex_cmd	*lex_cmd;

	while (*psr->pipes)
	{
		lex_cmd = lexer(*psr->pipes, data, pt);
		if (data->debug)
			printf("pipes returned pointer %p\n", lex_cmd);
		if (lex_cmd == NULL)
			return (-1);
		if (get_command_array(lex_cmd, psr, data) < 0)
			return (free(lex_cmd), -1);
		free(lex_cmd);
		if (psr->array != NULL)
			ft_lstadd_back(&pt->comm, ft_lstnew((void **) psr->array));
		psr->pipes++;
	}
	return (1);
}
