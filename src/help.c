/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: voparkan <voparkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 17:04:14 by voparkan          #+#    #+#             */
/*   Updated: 2024/07/07 17:11:51 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void    help()
{
    printf("minishell, version 0.1.1-release \
These shell commands are defined internally.  Type `help` to see this list. \
Type `help name` to find out more about the function `name`. \
Use `info bash` to find out more about the shell in general. \
Use `man -k` or `info` to find out more about commands not in this list. \
\
A star (*) next to a name means that the command is disabled.\
\
cd [-L|[-P [-e]] [-@]] [dir]\
echo [-neE] [arg ...]\
env\
export [-fn] [name[=value] ...] or export -p\
unset [-f] [-v] [-n] [name ...]");
}
