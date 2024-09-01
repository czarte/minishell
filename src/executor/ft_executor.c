/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: voparkan <voparkan@student.42prague.cz>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:07:28 by voparkan          #+#    #+#             */
/*   Updated: 2024/09/01 22:00:27 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"
#include "../../incl/executor.h"

void	ft_exec_child(t_executor *pt, t_list *com, int pi[2], int fd_m)
{
	char	**argv;
	int		exit_code;

	if (pt->heredoc)
		pt->fsucc = init_in_file(pt);
	argv = (char **) com->content;
	if (com->prev && dup2(fd_m, STDIN_FILENO) < 0)
		perror("unable to dup fd_m\n");
	if (!pt->heredoc)
		close(pi[0]);
	if (com->next && dup2(pi[1], STDOUT_FILENO) < 0)
		perror("unable to dup pi[1]\n");
	close(pi[1]);
	if (com->prev)
		close(fd_m);
	exit_code = execve(argv[0], &argv[1], pt->env);
	exit(exit_code);
}

int	create_heredoc(t_executor *pt)
{
	char	*name;
	int		fd;

	name = ft_join_path(pt->pwd, ".tmp_heredoc");
	fd = init_hd_file(name, pt);
	return (fd);
}

int	send_heredoc(t_executor *pt)
{
	int		file;
	char	*line;

	if (!pt->heredoc_rl)
		return (0);
	file = create_heredoc(pt);
	line = readline(">");
	while (line && ft_strncmp(pt->dlmtr, line, ft_strlen(pt->dlmtr)))
	{
		write(file, line, ft_strlen(line));
		write(file, "\n", 1);
		free(line);
		line = readline(">");
	}
	free(line);
	close(file);
	return (1);
}

//void	run_builtin()
//{
//	if (str_comp(eb->cur->type, "bu") && data->n_cmd == 0)
//
//	else if (str_comp(eb->cur->type, "vd"))
//		envp_add_reallocate(data, eb->cur->token, 1);
//}

int	ft_exec(t_executor *pt, int pi[2], int fd_m, t_data *data)
{
	static int	i;

	if (pt->end)
	{
		i = 0;
		pt->end = 0;
	}
	printf("executor: %s\n", (char *) pt->comm->content[0]);
	if (is_builtin((char *) pt->comm->content[0], data)) {
		//execute_builtin(pt->comm->content[0], pt);
	}
	else
	{
		send_heredoc(pt);
		pt->pid[i] = fork();
		g_pid = pt->pid[i];
		if (pt->pid[i] == -1) {
			perror("fork error");
			exit(EXIT_FAILURE);
		}
		if (pt->pid[i] == 0)
			ft_exec_child(pt, pt->comm, pi, fd_m);
		i++;
	}
	return (EXIT_SUCCESS);
}
