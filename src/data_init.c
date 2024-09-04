/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:08:03 by voparkan          #+#    #+#             */
/*   Updated: 2024/09/03 15:10:11 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

/**
 * Allocates and initializes array with builtin command names
 */
int	init_builtins(t_data *data)
{
	data->builtins = malloc(sizeof(char *) * 8);
	if (!data->builtins)
	{
		perror("builtins:");
		return (-1);
	}
	null_builtins(data);
	allocate_builtins(data);
	fill_builtins(data);
	return (0);
}

int	data_perror(t_data *data, char *msg)
{
	perror(msg);
	free_data(data);
	return (-1);
}

int	exec_data_init(t_data *data)
{
	data->exec = malloc(sizeof(t_exec));
	if (data->exec == NULL)
		return (data_perror(data, "exec_struct"));
	data->exec->cmd = NULL;
	data->exec->infile = NULL;
	data->exec->outfile = NULL;
	data->exec->append = false;
	data->exec->limit = false;
	data->exec->dlmtr = NULL;
	return (0);
}

int	exec_data_re_init(t_data *data)
{
	if (data->exec == NULL)
		return (data_perror(data, "exec_struct"));
	data->exec->cmd = NULL;			//TODO presunout jinam
	data->exec->infile = NULL;
	data->exec->outfile = NULL;
	data->exec->append = false;
	data->exec->limit = false;
	data->exec->dlmtr = NULL;
	return (0);
}

/**
 * Main data initialization routine
 */
int	data_init(t_data *data, char **envp)
{
	data->debug = true;
	data->cmd_list = NULL;
	data->token_chain = NULL;
	data->builtins = NULL;
	data->exec = NULL;
	data->envp = envp;
	data->lexer_list = NULL;
	data->local_temp_envp = NULL;
	if (envp_add_reallocate(data, NULL, 0))
		return (-1);
	data->cmd_list = malloc(sizeof(t_cmd_list));
	if (data->cmd_list == NULL)
		return (data_perror(data, "cmd_list"));
	data->cmd_list->cmd = NULL;
	data->cmd_list->full_path = NULL;
	data->cmd_list->next = NULL;
	data->last_c_l_node = data->cmd_list;
	data->token_chain = malloc(sizeof(t_token_chain));
	if (data->token_chain == NULL)
		return (data_perror(data, "token_list"));
	data->token_chain->token = NULL;
	data->token_chain->next = NULL;
	data->work_dir = getcwd(NULL, 0);
	init_builtins(data);
	return (0);
}
