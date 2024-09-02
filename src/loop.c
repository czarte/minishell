/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by voparkan          #+#    #+#             */
/*   Updated: 2024/08/24 14:26:49 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"
#include "../incl/executor.h"

void	ft_exit(char *cmd)
{
	if (!cmd)
		return ;
	cmd_space_trim(cmd);
	while (*cmd)
	{
		if (*cmd >= '0' && *cmd <= '9')
		{
			g_last_status = ft_atoi(cmd);
			return ;
		}
		cmd++;
	}
}

bool	is_exit_cmd(char *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return (true);
	while (cmd[i] == ' ')
		i++;
	if (cmd[i] == 'e' && cmd[i + 1] == 'x' && cmd[i + 2] == 'i'
		&& cmd[i + 3] == 't')
		return (true);
	return (false);
}

void	init_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

int	refresh_path(t_data *data)
{
	free_cmd_list(data);
	if (get_cmd_list(data) < 0)
		return (-1);
	return (0);
}

int	loop(t_data *data)
{
	char			*cmd;
	t_executor		*pt;

	if (exec_data_init(data) < 0)
		return (-1);
	init_signals();
	while (true)
	{
		cmd = cli(data);
		pt = ft_init_exec(data);
		if (is_exit_cmd(cmd) || (refresh_path(data) < 0))
		{
			ft_exit(cmd);
			free(cmd);
			return (clear_history(), g_last_status);
		}
		if (!*cmd)
		{
			free(cmd);
			continue ;
		}
		if (ft_parse_command(pt, cmd, data))
			g_last_status = executor(data, pt);
		pt = NULL;
		free_token_chain(data);
	}
}
