#include "../../incl/minishell.h"

int	num_of_vars(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i] != NULL)
		i++;
	return (i);
}

int	copy_add_envp(char **new_envp, char **envp, char *new_var)
{
	int	i;

	i = 0;
	while (envp && envp[i])
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
	while (envp && envp[i])
	{
		free(envp[i]);
		envp[i] = NULL;
		i++;
	}
	free(envp);
}

//TODO check if it works correctly
int	check_envp_for_duplicate(char **envp, char *new_var)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!envp || !new_var)
		return (-1);
	while (envp[i])
	{
// 		printf("%s %s\n", envp[i], new_var);
		while(envp[i][j] == new_var[j] && new_var[j] != '=')
			j++;
		if (envp[i][j] == '=' && (new_var[j] == '=' || new_var[j] == '\0'))
			return (i);
		j = 0;
		i++;
	}
	return (-1);
}

int	update_envp_var(char **envp, char *new_var, int	v_pos)
{
	int	i;

	i = 0;
	if (v_pos >= 0)
		printf("envp [%i] update original: %s\n", v_pos, envp[v_pos]);
	if (v_pos == -1)
		return (1);
	free(envp[v_pos]);
	envp[v_pos] = NULL;
	envp[v_pos] = malloc(ft_strlen(new_var) + 1);
	while (new_var[i])
	{
		envp[v_pos][i] = new_var[i];
		i++;
	}
	envp[v_pos][i] = '\0';
	return (0);
}

//TODO
//		create export function that takes temporary env var and saves it into data->envp

/**
 * Adds environment variable to the local environment
 * if temp == 0 it works with local environment
 * if temp == 1 it works with temporary variables declared by 'VAR=VALUE'
 */
int	envp_add_reallocate(t_data *data, char *new_var, char temp)
{
	char	**new_envp;
	char	**old_envp;
	int		n_o_v;
	int		i;
	int		ret;

	n_o_v = 0;
	i = 0;
	new_envp = NULL;
	ret = 0;
	if (temp)
		old_envp = data->local_temp_envp;
	else
		old_envp = data->envp;
	ret = update_envp_var(old_envp, new_var, check_envp_for_duplicate(old_envp, new_var));
	if (ret == 0 || ret == -1)
		return (ret);
	n_o_v = num_of_vars(old_envp);
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
	if (copy_add_envp(new_envp, old_envp, new_var))
		return (-1);
	if (new_var)
		free_old_envp(old_envp);
	if (temp)
		data->local_temp_envp = new_envp;
	else
		data->envp = new_envp;
	return (0);
}
