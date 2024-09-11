/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:04:05 by voparkan          #+#    #+#             */
/*   Updated: 2024/09/07 11:46:12 by voparkan         ###   ########.fr       */
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

typedef struct s_bag_struct
{
	char		**pipes;
	char		**splitcmd;
	char		**array;
	char		*pathcmd;
	char		*combined;
	t_executor	*pt;
}	t_bagp;

typedef struct s_data	t_data;

typedef struct s_exec_bag
{
	t_token_chain	*cur;
	bool			run;
}	t_exec_bag;

t_executor	*ft_init_exec(t_data *data);
void		ft_exec_child(t_executor *pt, t_list *com, int pi[2], int fd_m);
int			ft_exec(t_executor *pt, int pi[2], int fd_m);
int			ft_loop(t_executor *pt, int fd_m);
void		free_alloc(t_executor *pt);
int			execute_builtin(void **current, t_data *data);
int			command_arg_count(t_token_chain *tc, t_data *data);
void		assign_pt(t_data *data, t_executor *pt);

/* Parser */

char 		**parse_argv(char *arg, t_executor *pt, t_data *data);
int			ft_parse_command(t_executor *pt, char *argv, t_data *data);
int			get_command_array(t_lex_cmd *lex_cmd, t_bagp *psr, t_data *data);
int			iterate_splited(t_executor *pt, t_data *data, t_bagp *psr);
int			extract_simple(char *arg, t_executor *pt, t_data *data, t_bagp *psr);
void		appedn_command_bits(t_bagp *psr, char **tmp, t_data *data);
int			get_simple_cmd_array(t_lex_cmd *lex_cmd, t_bagp *psr, t_data *data);
int			create_array(t_lex_cmd *lex_cmd, t_bagp *psr, t_data *data, \
	char **tmp);
void		print_debug_array(t_bagp *psr);
void 		prepare_piped_array(t_lex_cmd *lex_cmd, t_bagp *psr, const t_data \
	*data, char **prepare);
char 		**granulate_command(t_bagp *psr, const t_data *data, char **tmp);
void 		print_debug_tmp_split(char **splitcmd, char **tmp);
int			count_splited(char **cmd);
void 		trim_all(char **splitcmd);
char		**ft_skip_quote_split(char const *s, char c);
char		*ft_skip_quote_strrchr(const char *s, int c);

/* utils */
void		ft_check_access(char *pathcmd, char ***array, t_executor *pt);
void 		print_debug_array(t_bagp *psr);
int			wait_subprocess(t_executor *pt, int n);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		ft_lstclear(t_list **lst, void (*del)(void**, t_executor*), \
	t_executor *pt);
void		ft_lstdelone(t_list *lst, void (*del)(void**, t_executor*), \
	t_executor *pt);
void		ft_lstadd_back(t_list **lst, t_list *nlist);
t_list		*ft_lstlast(t_list *lst);
t_list		*ft_lstnew(void **content);
char		*ft_strrchr(const char *s, int c);
char		*open_infile(t_executor *pt, char *filename);
int 		check_commands(t_executor *pt);
int			init_in_file(t_executor *pt);
int			init_out_file(t_executor *pt, int pi[2]);
int			init_hd_file(char *file, t_executor *pt);
int			check_heredoc(t_executor *pt, int pi[2]);

#endif // !EXECUTOR_H
