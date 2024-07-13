#include"../../incl/minishell.h"

void signal_handler(int signum)
{
    if (signum == SIGINT)
    {
        if (pid)
        {
            printf("\nSIGINT for pid: %i\n", pid);  //for debug
            kill(pid, SIGINT);
            pid = 0;
        }
    }
}
