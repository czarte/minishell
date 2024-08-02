/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: voparkan <voparkan@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by voparkan          #+#    #+#             */
/*   Updated: 2024/07/28 16:18:24 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"
#include "../incl/executor.h"

int    loop(t_data *data)
{
    int    exit_code;
    char   *cmd;
    struct sigaction sa;

    if (exec_data_init(data) < 0)
        return (-1);
    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);
    write(1, &"cliup\n", 6);
    while(true)
    {
        cmd = cli(data);
        printf("loop: %s\n", cmd);
        if (!cmd)
            break ;
        lexer(cmd, data);
        exit_code = executor(data);
        free_token_chain(data);
    }
    clear_history();
    return(exit_code);
}
