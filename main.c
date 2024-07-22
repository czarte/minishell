/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: voparkan <voparkan@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by voparkan          #+#    #+#             */
/*   Updated: 2024/07/22 15:34:18 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

#include "./incl/minishell.h"

pid_t	pid;

int main(int argc, char **argv, char **envp)
{
	t_data *data;

	if (argc != 1)
		return (0);
	argv++;
	(void)argv;
	// print_env(envp);
	data = malloc(sizeof(t_data));
	if (data == NULL)
	{
		perror("Main data struct: ");
		return (-1);
	}
	if(data_init(data, envp) == -1)
		return (-1);
	if (get_cmd_list(data) == -1)
		return (-1);
	// printf("look for: %s, path: %s\n", "ls", get_cmd_path("ls", data));
	// printf("look for: %s, path: %s\n", "pwd", get_cmd_path("pwd", data));
	// printf("look for: %s, path: %s\n", "nonexistent", get_cmd_path("nonexistent", data));
	// printf("current working directory: %s\n", data->work_dir);
	// cd("src", data);
	// printf("current working directory: %s\n", data->work_dir);
	loop(data);
	free_data(data);
	return (0);
}
