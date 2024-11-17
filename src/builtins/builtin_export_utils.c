/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 17:52:43 by voparkan          #+#    #+#             */
/*   Updated: 2024/11/14 09:27:33 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

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

int	num_of_vars(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i] != NULL)
		i++;
	return (i);
}

int	copy_add_envp(char **new_envp, char **envp, char *new_var)
{
	int	i;

	i = 0;
	while (envp && envp[i])
	{
		new_envp[i] = ft_memdup(envp[i]);
		if (new_envp[i] == NULL)
		{
			perror("Copying envp");
			return (-1);
		}
		i++;
	}
	if (new_var)
	{
		new_envp[i] = ft_memdup(new_var);
		if (new_envp[i] == NULL)
		{
			perror("Copying envp");
			return (-1);
		}
	}
	return (0);
}

void	free_old_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
	{
		free(envp[i]);
		envp[i] = NULL;
		i++;
	}
	free(envp);
}

int	check_envp_for_dupl(char **envp, char *new_var)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!envp || !new_var)
		return (-1);
	while (envp[i])
	{
		while (envp[i][j] == new_var[j] && new_var[j] != '=')
			j++;
		if (envp[i][j] == '=' && (new_var[j] == '=' || new_var[j] == '\0'))
			return (i);
		j = 0;
		i++;
	}
	return (-1);
}
