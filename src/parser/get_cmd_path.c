/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 01:35:28 by smelicha          #+#    #+#             */
/*   Updated: 2024/07/30 10:04:03 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

/**
 * Function to retrive executables path for particular command,
 * returns pointer to the string
 * RETURN OF THIS FUNCTION SHOULD NOT BE FREED AFTER USE IN CALLING FUNCTION!!!
 */
char	*get_cmd_path(const char *cmd, t_data *data)
{
	t_cmd_list	*current;

	current = data->cmd_list->next;
	while (current)
	{
		if (str_comp(cmd, current->cmd))
			return (ft_memcpy(current->full_path));
		else
			current = current->next;
	}
	return (NULL);
}
