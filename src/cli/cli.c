/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: voparkan <voparkan@student.42heilbronn.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 17:52:43 by voparkan          #+#    #+#             */
/*   Updated: 2024/07/22 15:51:17 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

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
		data->prompt[i] = ' ';
		data->prompt[i+1] = '$';
		data->prompt[i+2] = ':';
		data->prompt[i+3] = ' ';
		data->prompt[i+4] = '\0';
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
		data->prompt[i] = ' ';
		data->prompt[i+1] = '$';
		data->prompt[i+2] = ':';
		data->prompt[i+3] = ' ';
		data->prompt[i+4] = '\0';
	}
}

/**
 * Command line interface function with loop that where commands are recieved
 * and sent for further processing
 */
char	*cli(t_data *data)
{
	char	*cmd;

//	rl_catch_signals = 0;
//	rl_change_environment = 0;
	create_prompt(data);
	cmd = readline(data->prompt);
	write(1, &"cli\n", 4);
	printf("cli: %s\n", cmd);
	if (str_comp(cmd, "exit") || !cmd)
	{
		free(cmd);
		return (NULL);
	}
	if (cmd)
	{
		add_history(cmd);
	}
	return (cmd);
}
