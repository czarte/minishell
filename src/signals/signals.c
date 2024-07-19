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
