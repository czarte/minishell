#include "../incl/minishell.h"

int	num_of_vars(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
		i++;
	return (i);
}

int	copy_add_envp(char **new_envp, char **envp, char *new_var)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		new_envp[i] = ft_memcpy(envp[i]);
		if (new_envp[i] == NULL)
		{
			perror("Copying envp");
			return (-1);
		}
		i++;
	}
	if (new_var)
	{
		new_envp[i] = ft_memcpy(new_var);
		if (new_envp[i] == NULL)
		{
			perror("Copying envp");
			return (-1);
		}
	}
	return (0);
}

void	free_old_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		envp[i] = NULL;
		i++;
	}
	free(envp);
}

//TODO
//		test adding new entry
//		add a new type of token, local env val, and another datastructure to support these temporary env vars
//		create export function that takes temporary env var and saves it into data->envp

int	envp_add_reallocate(t_data *data, char *new_var)
{
	char	**new_envp;
	int		n_o_v;
	int		i;

	n_o_v = 0;
	i = 0;
	new_envp = NULL;
	n_o_v = num_of_vars(data->envp);
	if (new_var)
		n_o_v++;
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
	if (copy_add_envp(new_envp, data->envp, new_var))
		return (-1);
	if (new_var)
		free_old_envp(data->envp);
	data->envp = new_envp;
	return (0);
}
