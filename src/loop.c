/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by voparkan          #+#    #+#             */
/*   Updated: 2024/08/06 13:30:09 by smelicha         ###   ########.fr       */
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
	if (!cmd)
		return (true);
	while (*cmd == ' ')
		cmd++;
	if (*cmd == 'e')
		cmd++;
	if (*cmd == 'x')
		cmd++;
	if (*cmd == 'i')
		cmd++;
	if (*cmd == 't')
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

int	loop(t_data *data)
{
	char				*cmd;

	if (exec_data_init(data) < 0)
		return (-1);
	init_signals();
	if (data->debug)
		write(1, &"cliup\n", 6);
	while (true)
	{
		cmd = cli(data);
		if (data->debug)
			printf("loop: %s\n", cmd);
		if (is_exit_cmd(cmd))
		{
			ft_exit(cmd);
			free(cmd);
			return (clear_history(), g_last_status);
		}
		if (lexer(cmd, data) == 0)
			g_last_status = executor(data);
		free_token_chain(data);
	}
}
