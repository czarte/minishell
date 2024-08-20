/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: voparkan <voparkan@student.42prague.cz>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:10:53 by voparkan          #+#    #+#             */
/*   Updated: 2024/08/06 14:53:32 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"
#include "../../incl/executor.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*c;
	unsigned char	*d;

	c = (unsigned char *) s1;
	d = (unsigned char *) s2;
	while (n--)
		if (*c++ != *d++ || (!*(c - 1) || !*(d - 1)))
			return (*(c - 1) - *(d - 1));
	return (0);
}

int	wait_subprocess(t_executor *pt, int n)
{
	int	pid;
	int	exit_code;
	int	status;

	exit_code = 0;
	pid = 1;
	while (pid != -1)
	{
		pid = waitpid(pt->pid[n], &status, WNOHANG);
		if (pid == pt->pid[n])
			exit_code = WEXITSTATUS(status);
	}
	return (exit_code);
}

void	exec_data_prep_fill(t_data *data, t_token_chain **tc, int *i)
{
	char			**cmd;
	int				arg_count;

	*i = 2;
	arg_count = command_arg_count(*tc, data);
	cmd = malloc(sizeof(char *) * (arg_count + 3));
	cmd[arg_count + 2] = NULL;
	cmd[0] = get_cmd_path((*tc)->token, data);
	cmd[1] = ft_memdup((*tc)->token);
	*tc = (*tc)->next;
	while (*tc && str_comp((*tc)->type, "ar"))
	{
		cmd[(*i)] = ft_memdup((*tc)->token);
		if ((*tc)->next && str_comp((*tc)->next->type, "ar"))
		{
			*tc = (*tc)->next;
			(*i)++;
		}
		else
			break ;
	}
	ft_lstadd_back(&data->exec->cmd, ft_lstnew((void *)cmd));
}

void	exec_data_prep_fill_binary(t_data *data, t_token_chain **tc, int *i)
{
	char	**cmd;
	int		arg_count;

	*i = 2;
	arg_count = command_arg_count(*tc, data);
	cmd = malloc(sizeof(char *) * (arg_count + 3));
	cmd[arg_count + 2] = NULL;
	cmd[0] = ft_memdup((*tc)->token);
	cmd[1] = ft_memdup(((*tc)->token + last_slash((*tc)->token) + 1));
	*tc = (*tc)->next;
	while (*tc && str_comp((*tc)->type, "ar"))
	{
		cmd[(*i)] = ft_memdup((*tc)->token);
		if ((*tc)->next && str_comp((*tc)->next->type, "ar"))
		{
			*tc = (*tc)->next;
			(*i)++;
		}
		else
			break ;
	}
	ft_lstadd_back(&data->exec->cmd, ft_lstnew((void *)cmd));
}

int	exec_data_preparation(t_data *data)
{
	t_token_chain	*tc;
	int				i;

	tc = data->token_chain->next;
	i = 2;
	while (tc)
	{
		if (tc->next && str_comp(tc->type, "ri"))
		{
			tc = tc->next;
			continue ;
		}
		if (str_comp(tc->type, "pr") || str_comp(tc->type, "bu"))
			exec_data_prep_fill(data, &tc, &i);
		else if (str_comp(tc->type, "bp"))
			exec_data_prep_fill_binary(data, &tc, &i);
		else if (tc && str_comp(tc->type, "ra"))
			data->exec->append = true;
		else if (tc && str_comp(tc->type, "rd"))
			data->exec->limit = true;
		if (tc)
			tc = tc->next;
	}
	return (0);
}
