/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 17:52:43 by voparkan          #+#    #+#             */
/*   Updated: 2024/07/19 17:51:09 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	prompt_finish(int i, t_data *data)
{
	data->prompt[i] = ' ';
	data->prompt[i + 1] = '$';
	data->prompt[i + 2] = ':';
	data->prompt[i + 3] = ' ';
	data->prompt[i + 4] = '\0';
}

/**
 * Simple function to make a string to display as a prompt for command
 * line interface
 */
void	create_prompt(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (ft_strlen(data->work_dir) < 60)
	{
		while (data->work_dir[i])
		{
			data->prompt[i] = data->work_dir[i];
			i++;
		}
		prompt_finish(i, data);
	}
	else
	{
		j = ft_strlen(data->work_dir) - 60;
		while (data->work_dir[j])
		{
			data->prompt[i] = data->work_dir[j];
			i++;
			j++;
		}
		prompt_finish(i, data);
	}
}

bool	contains_printables(char *str)
{
	if (!str)
		return (false);
	while (*str)
	{
		if (*str >= 33 && *str != 127)
			return (true);
		str++;
	}
	return (false);
}

/**
 * Command line interface function with loop that where commands are recieved
 * and sent for further processing
 */
int	cli(t_data *data)
{
	char	*cmd;

	while (1)
	{
		create_prompt(data);
		cmd = readline(data->prompt);
		if (str_comp(cmd, "exit") || !cmd)
		{
			free(cmd);
			break ;
		}
		lexer(cmd, data);
		executor(data);
		free_token_chain(data);
		if (contains_printables(cmd))
		{
			add_history(cmd);
			free(cmd);
		}
		printf("Exit status: %i\n", g_last_status);
	}
	clear_history();
	return (1);
}
