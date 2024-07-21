/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: voparkan <voparkan@student.42prague.cz>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:04:05 by voparkan          #+#    #+#             */
/*   Updated: 2024/07/21 20:38:08 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"
# include <errno.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_list
{
	void			**content;
	struct s_list	*next;
	struct s_list	*prev;
}	t_list;

typedef struct s_executor
{
	int		*fd;
	int 	fd_m;
	int		c_pi;
	int		filefd[2];
	int		it;
	int		end;
	int		argc;
	int		fsucc;
	int		psucc;
	int		status;
	int		*pid;
	char	*pwd;
	char	*home;
	t_list	*comm;
	char	**argv;
	char	**env;
	char	**path;
	char	*file[2];
}	t_executor;

typedef struct s_bag_struct
{
	char	**splitcmd;
	char	**array;
	char	*pathcmd;
	char	*combined;
}	t_bagp;

typedef struct s_data t_data;

t_executor	ft_init_exec(int argc, char **argv, t_data *data);
void		ft_exec_child(t_executor *pt, t_list *com, int pi[2]);
//void		ft_exec_parent(t_executor *pt);
void		ft_exec(t_executor *pt, int pi[2], int n);
char		**parse_argv(char *arg, t_executor *pt);
int			ft_parse_command(t_executor *pt, int argc, char **argv);
void		ft_loop(t_executor *pt);
int			check_path_and_files(t_executor *pt);
void		print_help(void);
void		exit_error(t_executor *pt, int exitcode);
void		free_alloc(t_executor *pt);

/* utils */
int			wait_subprocess(t_executor *pt);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		ft_lstclear(t_list **lst, void (*del)(void*));
void		ft_lstdelone(t_list *lst, void (*del)(void*));
void		ft_lstadd_back(t_list **lst, t_list *nlist);
t_list		*ft_lstlast(t_list *lst);
t_list		*ft_lstnew(void *content);
char		*ft_strrchr(const char *s, int c);
char		*open_infile(t_executor *pt, char *filename);
void		check_commands(t_executor *pt);
int			init_in_file(t_executor *pt);
int			init_out_file(t_executor *pt);

#endif // !EXECUTOR_H