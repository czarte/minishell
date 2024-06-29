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
// 	printf("current: %p\n", current);
	printf("Local temp envp:\n");
	print_envp(data->local_temp_envp);
	if (data->local_temp_envp && current->next != NULL)
		printf("Can't decide what to export\n");
	else if (!data->local_temp_envp && current->next == NULL)
		printf("Nothing to export\n");
	else if (data->local_temp_envp && !data->local_temp_envp[1])
	{
		if (export_from_local(data))
		{
			perror("Export from local");
			return (-1);
		}
	}
	else if (!data->local_temp_envp && current->next)
	{
		if (export_from_token(current->next, data))
		{
			perror("Export from token");
			return (-1);
		}
	}
	else
		printf("Can't export :(\n");
	return (0);
}
