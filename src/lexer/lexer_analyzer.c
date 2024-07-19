/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_analyzer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:51:34 by stepan            #+#    #+#             */
/*   Updated: 2024/07/07 14:36:21 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

/**
 * Work in progress, will analyze pipes between programs
 */
int	analyze_redirections(t_data *data)
{
	t_token_chain	*current;

	current = data->token_chain->next;
	printf("Hello from redirections analyzer!\n");
	while (current)
	{
		if (str_comp(current->type, "ri") && current->next)
			type_token(current->next, "fp");
		if (str_comp(current->type, "rd") && current->next)
			type_token(current->next, "dl");
		if (str_comp(current->type, "ro") && current->next)
			type_token(current->next, "fp");
		if (str_comp(current->type, "ra") && current->next)
			type_token(current->next, "fp");
		current = current->next;
	}
	return (0);
}

char	*b_getenv(char *name, t_data *data)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (data->local_temp_envp && data->local_temp_envp[i])
	{
		while (data->local_temp_envp[i][j] == name[k])
		{
			j++;
			k++;
		}
		if (data->local_temp_envp[i][j] == '=')
			return (data->local_temp_envp[i] + j + 1);
		j = 0;
		k = 0;
		i++;
	}
	i = 0;
	while (data->envp && data->envp[i])
	{
		while (data->envp[i][j] == name[k])
		{
			j++;
			k++;
		}
		if (data->envp[i][j] == '=')
			return (data->envp[i] + j + 1);
		j = 0;
		k = 0;
		i++;
	}
	return (NULL);
}

/**
 * Expands the environment variable and makes an argument from it
 */
int	expand_env_var(t_token_chain *current, t_data *data)
{
	char	*env_var;
	char	*new_token;

	// var_name = current->token + 1;
	env_var = NULL;
	new_token = NULL;
	// printf("env var name: %s\n", var_name);
	env_var = b_getenv((current->token + 1), data);
	// printf("env var value: %s\n", env_var);
	new_token = ft_memcpy(env_var);
	if (!new_token && env_var)
	{
		perror("Allocation of expanded env var");
		return (-1);
	}
	// str_fill(new_token, env_var);
	free(current->token);
	// printf("new_token: %s\n", new_token);
	current->token = new_token;
	str_fill(current->type, "ar");
	return (0);
}

/**
 * Checks if the token chain contains environment variable to expand
 */
int	check_for_env_vars(t_data *data)
{
	t_token_chain	*current;

	current = data->token_chain->next;
	while (current)
	{
		if (str_comp(current->type, "ev"))
			if (expand_env_var(current, data))
				return (1);
		current = current->next;
	}
	return (0);
}

void	count_cmds(t_data *data)
{
	t_token_chain *current;

	current = data->token_chain->next;
	while (current)
	{
		if (str_comp(current->type, "pr"))
			data->n_cmd++;
		current = current->next;
	}
}

int	count_slashes(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == '/')
			i++;
		str++;
	}
	return (i);
}

bool	binary_is_in_list(char *name, char *path, t_data *data)
{
	t_cmd_list	*cmd_list;
	t_cmd_list	*prev;

	cmd_list = data->cmd_list;
	prev = NULL;
	while (cmd_list)
	{
		if (str_comp(name, cmd_list->cmd))
		{
			if (str_comp(path, cmd_list->full_path))
			{
				printf("Binary is already in the list!\n");
				return true;
			}
			else if (prev)
			{
				prev->next = cmd_list->next;
				free(cmd_list->cmd);
				free(cmd_list->full_path);
				free(cmd_list);
				return (false);
			}
		}
		prev = cmd_list;
		cmd_list = cmd_list->next;
	}
	return false;
}

/**
 * check for executing permission, if it is not executable, don't add it to the cmd list
 * check if the executable already is in the cmd list (same name and path; name can be the same
 * wih different paths or same path with different names)
 * 
 * 
 * In case of executing binary that is in the same working directory
 */
int	add_binary_cwd_path_to_commands(t_token_chain *current, t_data *data)
{
	char 	*name;
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
	if (!access(path, X_OK))
	{
		printf("\nExecutable OK!!!!!!!!\n\n");
		if (!binary_is_in_list(name, path, data))
			add_cmd_list_node(name, data->work_dir, data);
		type_token(current, "pr");
	}
	else
	{
		type_token(current, "ar");
		printf("\nExecutable NOT OK!!!\n\n");
	}
	printf("----Binary from abs path----\nname: %s\npath: %s\n", name, path);

	free(current->token);
	current->token = ft_memcpy(name);
	free(name);
	name = NULL;
	free(path);
	path = NULL;
	return (0);
}

/**
 * Gives back position of the last slah in the given string
 */
int last_slash(const char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == '/')
			j = i;
		str++;
		i++;
	}
	return (j);
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
	path = ft_memcpy((current->token + 1));
	if (!path)
	{
		perror("Binary abs path path allocation");
		return (-1);
	}
	if (!access(path, X_OK))
	{
		printf("\nExecutable OK!!!!!!!!\n\n");
		if (!binary_is_in_list(name, path, data))
			add_cmd_list_node(name, data->work_dir, data);
	}
	else
		printf("\nExecutable NOT OK!!!\n\n");

	printf("----Binary from abs path----\nname: %s\npath: %s\n", name, path);
	type_token(current, "pr");
	free(current->token);
	current->token = ft_memcpy(name);
	free(name);
	name = NULL;
	free(path);
	path = NULL;
	return (0);
}

int	check_for_binary_paths(t_data *data)
{
	t_token_chain	*current;

	current = data->token_chain->next;
	while (current)
	{
		if (str_comp(current->type, "bp") && count_slashes(current->token) == 1)
		{
			if (add_binary_cwd_path_to_commands(current, data))
				return (-1);
		}
		else if (str_comp(current->type, "bp") && count_slashes(current->token) > 1)
		{
			if (add_binary_abs_path_to_commands(current, data))
				return (-1);
		}
		current = current->next;
	}
	return (0);
}

/**
 * Main analyzing function
 * TODO add flags to main struct while creating the token chain what it contains so the chain doesn't need to be scanned for each type, like for env vars...
 */
int	token_chain_analyzer(t_data *data)
{
	if (check_for_env_vars(data))
		return (-1);
	analyze_redirections(data);
	check_for_binary_paths(data);
	count_cmds(data);
	return (0);
}
