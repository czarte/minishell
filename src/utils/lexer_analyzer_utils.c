/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_analyzer_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 18:59:34 by smelicha          #+#    #+#             */
/*   Updated: 2024/08/06 18:41:31 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

bool	add_binary_executabilty(char *name, char *path, t_token_chain *current,
			t_data *data)
{
	if (!access(path, X_OK))
	{
		if (!binary_is_in_list(name, path, data))
			add_cmd_list_node(name, data->work_dir, data);
		type_token(current, "pr");
		return (false);
	}
	else
	{
		type_token(current, "ar");
		printf("%s: Nonexistent or not executable!\n", name);
		return (true);
	}
}

int	add_binary_finish(char *name, char *path, t_token_chain *current,
		t_data *data)
{
	bool	invalid;

	invalid = add_binary_executabilty(name, path, current, data);
	free(current->token);
	current->token = ft_memcpy(name);
	if (!current->token)
	{
		perror("Allocating token for local binary");
		return (-1);
	}
	free(name);
	name = NULL;
	free(path);
	path = NULL;
	if (invalid)
		return (-1);
	else
		return (0);
}

/**
 * In case of executing binary that is in the same working directory
 */
int	add_binary_cwd_path_to_commands(t_token_chain *current, t_data *data)
{
	char	*name;
	char	*path;

	name = ft_memcpy((current->token + 2));
	if (!name)
	{
		perror("Binary cwd path name allocation");
		return (-1);
	}
	path = ft_strjoin(data->work_dir, name);
	if (!path)
	{
		perror("Binary cwd path path allocation");
		return (-1);
	}
	return (add_binary_finish(name, path, current, data));
}

/**
 * In case of executing binary using the absolute path
 */
int	add_binary_abs_path_to_commands(t_token_chain *current, t_data *data)
{
	char	*name;
	char	*path;

	name = ft_memcpy((current->token + last_slash(current->token) + 1));
	if (!name)
	{
		perror("Binary abs path name allocation");
		return (-1);
	}
	path = ft_memcpy((current->token));
	if (!path)
	{
		perror("Binary abs path path allocation");
		return (-1);
	}
	return (add_binary_finish(name, path, current, data));
}

int	check_for_binary_paths(t_data *data)
{
	t_token_chain	*current;

	current = data->token_chain->next;
	while (current)
	{
		if (str_comp(current->type, "bp") && count_slashes(current->token) == 1)
		{
			if (add_binary_cwd_path_to_commands(current, data) < 0)
				return (-1);
		}
		else if (str_comp(current->type, "bp")
			&& count_slashes(current->token) > 1)
		{
			if (add_binary_abs_path_to_commands(current, data) < 0)
				return (-1);
		}
		current = current->next;
	}
	return (0);
}
