/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_analyzer_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 18:59:34 by smelicha          #+#    #+#             */
/*   Updated: 2024/08/07 23:46:09 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

bool	add_binary_executabilty(char *path, t_token_chain *current)
{
	if (!access(path, X_OK))
		return (false);
	else
	{
		type_token(current, "ar");
		// printf("%s: Nonexistent or not executable!\n", name);
		return (true);
	}
}

int	add_binary_finish(char *name, char *path, t_token_chain *current)
{
	bool	invalid;

	invalid = add_binary_executabilty(path, current);
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

	name = ft_memdup((current->token + 2));
	if (!name)
	{
		perror("Binary cwd path name allocation");
		return (-1);
	}
	path = ft_join_path(data->work_dir, name);
	if (!path)
	{
		perror("Binary cwd path path allocation");
		return (-1);
	}
	return (add_binary_finish(name, path, current));
}

/**
 * In case of executing binary using the absolute path
 */
int	add_binary_abs_path_to_commands(t_token_chain *current)
{
	char	*name;
	char	*path;

	name = ft_memdup((current->token + last_slash(current->token) + 1));
	if (!name)
	{
		perror("Binary abs path name allocation");
		return (-1);
	}
	path = ft_memdup((current->token));
	if (!path)
	{
		perror("Binary abs path path allocation");
		return (-1);
	}
	return (add_binary_finish(name, path, current));
}

int	check_for_binary_paths(t_data *data)
{
	t_token_chain	*current;

	current = data->token_chain->next;
	while (current)
	{
		if (str_comp(current->type, "bp") && *current->token == '.')
		{
			if (add_binary_cwd_path_to_commands(current, data) < 0)
				return (-1);
		}
		else if (str_comp(current->type, "bp")
			&& count_slashes(current->token) > 1)
		{
			if (add_binary_abs_path_to_commands(current) < 0)
				return (-1);
		}
		current = current->next;
	}
	return (0);
}
