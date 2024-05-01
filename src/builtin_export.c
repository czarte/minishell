#include "../incl/minishell.h"

int	export_from_local(t_data *data)
{
	data++;
	data--;
	return (0);
}

int	export_from_token(t_token_chain *current, t_data *data)
{
	current++;
	current--;
	data++;
	data--;
	return (0);
}

/**
 * note: export() is reserved
 */
int	b_export(t_token_chain *current, t_data *data)
{
	if (data->local_temp_envp[0] && current->next != NULL)
		printf("Can't decide what to export\n");
	else if (!data->local_temp_envp[0] && current->next == NULL)
		printf("Nothing to export\n");
	else if (data->local_temp_envp[0] && !data->local_temp_envp[1])
	{
		if (export_from_local(data))
		{
			perror("Export from local");
			return (-1);
		}
	}
	else if (!data->local_temp_envp[0] && current->next)
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
