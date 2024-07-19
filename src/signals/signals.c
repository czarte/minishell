/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:10:31 by smelicha          #+#    #+#             */
/*   Updated: 2024/07/19 17:13:16 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../incl/minishell.h"

void signal_handler(int signum)
{
    if (signum == SIGINT)
    {
        if (pid > 0)
        {
            printf("\nSIGINT for pid: %i\n", pid);  //for debug
            kill(pid, SIGINT);
            pid = 0;
        }
        else
        {
            printf("\n");
            rl_on_new_line();
            rl_replace_line("", 0);
            rl_redisplay();
            return ;
        }
    }
}

void    signals_init(void)
{
    struct sigaction sa;

    rl_catch_signals = 0;
	rl_change_environment = 0;
    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}