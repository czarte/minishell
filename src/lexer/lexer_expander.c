/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 22:10:07 by smelicha          #+#    #+#             */
/*   Updated: 2024/09/01 18:55:59 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"
#include "../../incl/executor.h"

void	insert_env_join_strings(char *res, char *main1, char *main2, char *add)
{
	res = fill_res(res, main1);
	if (add)
	{
		res = fill_res(res, add);
		free(add);
	}
	res = fill_res(res, main2);
	*res = '\0';
}

char	*insert_env_string(int pos, char *main, char *add)
{
	char	*main1;
	char	*main2;
	char	*res;

	printf("main2 allocation: %ibytes\n", ft_strlen((main + pos)));
	main1 = malloc(sizeof(char) * (pos + 2));
	main2 = malloc(sizeof(char) * ft_strlen((main + pos)) + 4);
	res = malloc(sizeof(char) * (ft_strlen(main) + ft_strlen(add) + 2));
	split_main_string(main, main1, main2, pos);
	insert_env_join_strings(res, main1, main2, add);
	free(main1);
	free(main2);
	return (res);
}

int	expander_of_last_exit(int d_p, t_lex_cmd *lc)
{
	char	*tmp;

	tmp = lc->cmd;
	if (*(lc->cmd + d_p + 1) != '?')
		return (-1);
	lc->cmd = insert_env_string(d_p, lc->cmd, ft_itoa(g_last_status));
	free(tmp);
	return (0);
}

int	expander_of_env_var(int d_p, t_lex_cmd *lc, t_data *data)
{
	char	*var_name;
	char	*tmp;

	var_name = NULL;
	tmp = lc->cmd;
	if (!expander_of_last_exit(d_p, lc))
		return (0);
	var_name = get_var_name(d_p, lc);
	lc->cmd = insert_env_string(d_p, lc->cmd,
			ft_memdup(b_getenv(var_name, data)));
	free(tmp);
	free(var_name);
	return (0);
}

int	env_var_expander(t_lex_cmd *lc, t_data *data)
{
	int	dollar_pos;

	dollar_pos = ft_expandable(lc->cmd);
	if (dollar_pos < 0)
		return (0);
	else
		printf("position %i of env var: |%s|\n", dollar_pos, (lc->cmd + dollar_pos));
	expander_of_env_var(dollar_pos, lc, data);
	return (1);
}
