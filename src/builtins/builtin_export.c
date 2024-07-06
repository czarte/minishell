#include "../../incl/minishell.h"

int	export_from_local(t_data *data)
{
	if (envp_add_reallocate(data, data->local_temp_envp[0], 0))
	{
		perror("Export from local");
		return (-1);
	}
	free(data->local_temp_envp[0]);
	data->local_temp_envp[0] = NULL;
	return (0);
}

int	export_from_token(t_token_chain *current, t_data *data)
{
	if (envp_add_reallocate(data, current->token, 0))
	{
		perror("Export from token");
		return (-1);
	}
	return (0);
}

/**
 * Debug function
 */
void	print_envp(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
	{
		printf("NULL\n");
		return ;
	}
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
}

/**
 * note: export() is reserved
 */
int	b_export(t_token_chain *current, t_data *data)
{
	if (current->next)
	{
		if (export_from_token(current->next, data))
			return (-1);
	}
	if (!current->next)
	{
		printf("Should print what export without argument prints\n");
	}
	return (0);
}
