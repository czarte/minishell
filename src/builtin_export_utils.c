#include "../incl/minishell.h"

int	num_of_vars(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
		i++;
	return (i);
}

void	copy_envp(char **new_envp, char **envp)
{

}

int	envp_add_reallocate(t_data *data, char *new_var)
{
	char	**new_envp;
	int		n_o_v;
	int		i;

	n_o_v = 0;
	i = 0;
	new_envp = NULL;
	n_o_v = num_of_vars(data->envp);
	new_envp = malloc(sizeof(char*) * (n_o_v + 1));
	if (!new_envp)
	{
		perror("Envp reallocation");
		return (-1);
	}
	while (i != (n_o_v + 1))
	{
		new_envp[i] = NULL;
		i++;
	}
	return (0);
}
