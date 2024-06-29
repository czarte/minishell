#include "../../incl/minishell.h"

void	env(t_data *data)
{
	int		i;
	char	**envp;

	i = 0;
	envp = data->envp;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
}
