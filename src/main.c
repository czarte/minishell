/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 01:34:56 by smelicha          #+#    #+#             */
/*   Updated: 2024/04/06 18:25:07 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	printf("look for: %s, path: %s\n", "ls", get_cmd_path("ls", data));
	printf("look for: %s, path: %s\n", "pwd", get_cmd_path("pwd", data));
	printf("look for: %s, path: %s\n", "nonexistent", get_cmd_path("nonexistent", data));
	printf("current working directory: %s\n", data->work_dir);
	cd("src", data);
	printf("current working directory: %s\n", data->work_dir);
	cli(data);
	free_data(data);
	return (0);
}
