/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 01:35:28 by smelicha          #+#    #+#             */
/*   Updated: 2024/08/06 16:17:30 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"
#include <stdbool.h>

/**
 * Function to retrive executables path for particular command,
 * returns pointer to the string
 * RETURN OF THIS FUNCTION SHOULD NOT BE FREED AFTER USE IN CALLING FUNCTION!!!
 */
char	*get_cmd_path(const char *cmd, t_data *data)
{
	t_cmd_list	*current;

	if (!data->cmd_list)
		return (ft_memdup(cmd));
	current = data->cmd_list->next;
	while (current)
	{
		if (str_comp(cmd, current->cmd))
			return (ft_memdup(current->full_path));
		else
			current = current->next;
	}
	if (is_builtin((char *)cmd, data))
		return (ft_memdup("builtin"));
	return (NULL);
}

bool	check_cmd_path_exists(const char *cmd, t_data *data)
{
	t_cmd_list	*current;

	if (!data->cmd_list)
		return (false);
	current = data->cmd_list->next;
	while (current)
	{
		if (str_comp(cmd, current->cmd))
			return (true);
		else
			current = current->next;
	}
	if (is_builtin((char *) cmd, data))
		return(true);
	return (false);
}
