/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: voparkan <voparkan@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by voparkan          #+#    #+#             */
/*   Updated: 2024/08/05 22:00:08 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	pipe_less_gt(t_fill_t_c_data *ftcdata)
{
	while (*ftcdata->cmd != '|' && *ftcdata->cmd != '<' && *ftcdata->cmd != '>')
	{
		*ftcdata->token = *ftcdata->cmd;
		ftcdata->token++;
		ftcdata->cmd++;
	}
}

void	do_greater(t_fill_t_c_data *ftcdata)
{
	while (*ftcdata->cmd == '>')
	{
		*ftcdata->token = *ftcdata->cmd;
		ftcdata->cmd++;
		ftcdata->token++;
	}
}

void	do_lesser(t_fill_t_c_data *ftcdata)
{
	while (*ftcdata->cmd == '<')
	{
		*ftcdata->token = *ftcdata->cmd;
		ftcdata->cmd++;
		ftcdata->token++;
	}
}
