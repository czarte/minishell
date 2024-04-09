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

#include "../incl/minishell.h"

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

int	cli(t_data *data)
{
	char	*cmd;
	char	*path;

	while (1)
	{
		create_prompt(data);
		cmd = readline(data->prompt);
		path = get_cmd_path(cmd, data);
		// if (path)
		// 	printf("%s\n", path);
		// else
		// 	printf("(null)\n");
		if (str_comp(cmd, "exit"))
		{
			free(cmd);
			break ;
		}
		if (cmd)
		{
			add_history(cmd);
			free(cmd);
		}
		lexer(cmd, data);
	}
	rl_clear_history();
	return (1);
}
