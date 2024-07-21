/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_free_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 19:51:26 by smelicha          #+#    #+#             */
/*   Updated: 2024/07/21 19:51:48 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	free_folder_strs(char **folder_strs)
{
	int	i;

	i = 0;
	while (folder_strs[i] != NULL)
	{
		free(folder_strs[i]);
		i++;
	}
	free(folder_strs);
}
