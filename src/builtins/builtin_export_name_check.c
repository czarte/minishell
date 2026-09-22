/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:20:41 by smelicha          #+#    #+#             */
/*   Updated: 2024/11/14 09:29:45 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

bool	forbidden_characters_err_mes(char *var)
{
	ft_putstr_fd("export: \'", 2);
	ft_putstr_fd(var, 2);
	ft_putstr_fd("\': not a valid identifier\n", 2);
	g_last_status = 1;
	return (true);
}

bool	is_cap_alpha(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (true);
	return (false);
}

bool	is_low_alpha(char c)
{
	if (c >= 'a' && c <= 'z')
		return (true);
	return (false);
}

bool	is_num(char c)
{
	if (c >= '0' && c <= '9')
		return (true);
	return (false);
}

bool	forbidden_cahracters(char *var)
{
	char	*tmp_var;

	tmp_var = var;
	if (!var)
		return (false);
	while (*var && *var != '=')
	{
		if (is_cap_alpha(*var) || is_low_alpha(*var) || is_num(*var)
			|| *var == '_' || *var == '=')
			var++;
		else
		{
			forbidden_characters_err_mes(tmp_var);
			return (true);
		}
	}
	return (false);
}
