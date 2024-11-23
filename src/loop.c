/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by voparkan          #+#    #+#             */
/*   Updated: 2024/09/19 13:49:27 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"
#include "../incl/executor.h"

bool	is_num(char *str)
{
	while (*str)
	{
		if ((*str < '0' || *str > '9') && *str != '-')
			return (false);
		str++;
	}
	return (true);
}

int	count_double_char_strings(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

void	ft_exit_too_many_args(void)
{
	ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	g_last_status = 1;
}

void	ft_exit_not_number(char *str)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	g_last_status = 2;
}

void	ft_exit(char *cmd)
{
	int	i;
	char **splitted;

	splitted = NULL;
	i = 0;
	if (!cmd)
		return ;
	cmd_trim(cmd, ' ');
	splitted = ft_split(cmd, ' ');
	printf("exit\n");
	if (!is_num(splitted[1]))
		ft_exit_not_number(splitted[1]);
	else if (count_double_char_strings(splitted) > 2)
		ft_exit_too_many_args();
	else
		g_last_status = ft_atoi(splitted[1]);
	while (splitted[i])
		free(splitted[i++]);
	free(splitted);
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
	{
		if (cmd[i + 4] == ' ')
			return (true);
	}
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
			free_pt_cmd(pt, cmd);
			return (clear_history(), g_last_status);
		}
		if (!*cmd || only_char(cmd, ' '))
		{
			free_pt_cmd(pt, cmd);
			continue ;
		}
		if (ft_parse_command(pt, cmd, data))
			g_last_status = executor(data, pt);
		pt = NULL;
	}
}
