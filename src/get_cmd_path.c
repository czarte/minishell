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

int	str_comp(const char *str1, const char *str2)
{
	int	i;

	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] == str2[i])
			i++;
		else
			return (0);
	}
	if (str1[i] || str2[i])
		return (0);
	return (i);
}

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
	printf("retruning null from get_cmd_path\n");
	return (NULL);
}
