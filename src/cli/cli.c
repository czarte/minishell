/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: voparkan <voparkan@student.42heilbronn.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 17:52:43 by voparkan          #+#    #+#             */
/*   Updated: 2024/06/30 09:54:44 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 18:17:28 by smelicha          #+#    #+#             */
/*   Updated: 2024/04/06 23:00:14 by smelicha         ###   ########.fr       */
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
int	cli(t_data *data)
{
	char	*cmd;

	while (1)
	{
		signal(SIGINT, signal_handler);
		create_prompt(data);
		cmd = readline(data->prompt);
		if (str_comp(cmd, "exit"))
		{
			free(cmd);
			break ;
		}
		lexer(cmd, data);
		if (cmd)
		{
			add_history(cmd);
			free(cmd);
		}
	}
	clear_history();
	return (1);
}
