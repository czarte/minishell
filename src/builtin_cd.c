/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 01:35:47 by smelicha          #+#    #+#             */
/*   Updated: 2024/04/02 01:45:53 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	cd(const char *new_wd, t_data *data)
{
	if (chdir(new_wd) != 0)
	{
		perror("");
		return ;
	}
	getcwd(data->work_dir, sizeof(data->work_dir));
}