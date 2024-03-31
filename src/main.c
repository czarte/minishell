#include "../incl/minishell.h"

int main(void)
{
	t_data *data;

	data = malloc(sizeof(t_data));
	if (data == NULL)
	{
		perror("Main data struct: ");
		return (-1);
	}
	if(data_init(data) == -1)
		return (-1);
	if (get_cmd_list(data) == -1)
		return (-1);
	free_data(data);
    return (0);
}
