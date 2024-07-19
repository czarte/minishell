/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: voparkan <voparkan@student.42prague.cz>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 11:07:34 by voparkan          #+#    #+#             */
/*   Updated: 2024/07/19 11:52:54 by voparkan         ###   ########.fr       */
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
            //rl_replace_line("", 0);
            rl_redisplay();
            return ;
        }
    }
}
