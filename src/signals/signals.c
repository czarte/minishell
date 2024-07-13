#include "../../incl/minishell.h"

void signal_handler(int signum)
{
    if (signum == SIGINT)
    {
        printf("Signal received!\n");
    }
}
