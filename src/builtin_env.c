#include "../incl/minishell.h"

void	print_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
}

int	env(t_token_chain *current, t_data *data)
{
	if (!current->next)
		print_env(data->envp);
	return (0);
}
