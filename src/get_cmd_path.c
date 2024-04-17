/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 01:35:28 by smelicha          #+#    #+#             */
/*   Updated: 2024/04/06 20:13:16 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

// void	get_alternatives(const char *cmd, t_data *data)
// {
// 	t_cmd_list	*current;

// 	current = data->cmd_list->next;
// 	while (current)
// 	{
// 		if (str_comp(cmd, current->cmd))
// 			printf("%s\n", current->full_path);
// 		current = current->next;
// 	}
// }

/**
 * Function to retrive executables path for particular command, returns pointer to
 * the string
 * RETURN OF THIS FUNCTION SHOULD NOT BE FREED AFTER USE IN CALLING FUNCTION!!!
 */
char	*get_cmd_path(const char *cmd, t_data *data)
{
	t_cmd_list	*current;

	// get_alternatives(cmd, data);
	current = data->cmd_list->next;
	while (current)
	{
		if (str_comp(cmd, current->cmd))
			return (current->full_path);
		else
			current = current->next;
	}
	// printf("retruning null from get_cmd_path\n");
	return (NULL);
}
