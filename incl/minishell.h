/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 20:04:38 by voparkan          #+#    #+#             */
/*   Updated: 2024/08/17 14:19:46 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 01:35:17 by smelicha          #+#    #+#             */
/*   Updated: 2024/07/07 14:35:44 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _POSIX_C_SOURCE 200809L

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <signal.h>
# include <fcntl.h>
# include <dirent.h>
# include <libgen.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <termcap.h>

# define N_BUILTINS 8
/**
 * Global variable for pid of currently running process
 */
extern pid_t					g_pid;
extern int						g_last_status;

typedef struct s_cmd_list		t_cmd_list;
typedef struct s_token_chain	t_token_chain;

typedef struct s_cmd_list
{
	char		*cmd;
	char		*full_path;
	t_cmd_list	*next;
}	t_cmd_list;

typedef struct s_list
{
	void			**content;
	struct s_list	*next;
	struct s_list	*prev;
}	t_list;

/*
 type:
	pr	program
	bp	binary path			./binary or /home/user/folder/binary
	bu	builtin
	ar	argument
	fp	file path
	pi	pipe				|
	ri	redirect input		<
	ro	redirect output		>
	rd	redirect delimiter	<<
	dl	delimiter
	ra	redirect append		>>
	ev	environment var		$something
	vd	variable declar.	VAR_NAME=VALUE
	es	last pi ex. stat.	$?
 */
typedef struct s_token_chain
{
	char			*token;
	char			type[3];
	bool			expand;
	t_token_chain	*next;
}	t_token_chain;

typedef struct s_lex_cmd
{
    char             *cmd;
    char             dlmtr;
    bool             split;
}	t_lex_cmd;

typedef struct s_exec_data
{
	t_list	*cmd;
	char	*infile;
	char	*outfile;
	char	*dlmtr;
	bool	limit;
	bool	append;
}	t_exec;

/**
 * Struct used in the envp manipulation function
 */
typedef struct s_envp_a_r_data
{
	char	**new_envp;
	char	**old_envp;
	int		n_o_v;
	int		i;
	int		ret;
}	t_envp_a_r_data;

typedef struct s_fill_t_c_data
{
	t_token_chain	*current;
	char			*token;
	char			*cmd;
	char			quote;
}	t_fill_t_c_data;

/**
 * Main data struct
 */
typedef struct s_data
{
	bool				debug;
	t_cmd_list			*cmd_list;
	t_token_chain		*token_chain;
	t_cmd_list			*last_c_l_node;
	t_list				*lexer_list;
	t_exec				*exec;
	char				**envp;
	char				**builtins;
	char				**local_temp_envp;
	char				work_dir[4096];
	char				prompt[66];
	int					n_cmd;
}	t_data;

typedef struct s_token_bag
{
	char	quote;
	bool	first_run;
}	t_token_bag;

typedef struct s_executor
{
	bool	deubg;
	bool	heredoc;
	bool	heredoc_rl;
	bool	append;
	int		*fd;
	int		c_pi;
	int		filefd[2];
	int		it;
	int		end;
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
	char	*infile;
	char	*outfile;
	char	*dlmtr;	//heredoc delimiter
}	t_executor;

int		loop(t_data *data);
int		ft_parser(char *cmd, t_data *data);

/*----    Data functions    ----*/
int		data_init(t_data *data, char **envp);
int		exec_data_init(t_data *data);
int		free_data(t_data *data);
void	free_cmd_list(t_data *data);
void	free_token_chain(t_data *data);
void	free_exec(t_data *data);
void	free_folder_strs(char **folder_strs);
int		data_perror(t_data *data, char *msg);
void	fill_builtins(t_data *data);
void	null_builtins(t_data *data);
int		allocate_builtins(t_data *data);
void	print_token_chain(t_data *data);
void	free_exec_files(t_data *data);

/*----    Data preparation    ----*/
int		get_cmd_list(t_data *data);
int		exec_data_re_init(t_data *data);

/*----    Command functions    ----*/
char	*get_cmd_path(const char *cmd, t_data *data);
bool	check_cmd_path_exists(const char *cmd, t_data *data);
int		add_cmd_list_node(char *name, char *path, t_data *data);

/*----    Builtin commands functions    ----*/
void	cd(const char *new_wd, t_data *data);
void	echo(t_token_chain *echo_tok);
void	env(t_data *data);
int		b_export(t_token_chain *current, t_data *data);
int		unset(t_token_chain *current, t_data *data);

/*----    Builtin utils    ----*/
int		envp_add_reallocate(t_data *data, char *new_var, char temp);
void	free_old_envp(char **envp);
int		check_envp_for_duplicate(char **envp, char *new_var);
int		num_of_vars(char **envp);
int		copy_add_envp(char **new_envp, char **envp, char *new_var);
void	print_envp(char **envp);
char	*b_getenv(char *name, t_data *data);
char	*get_env_check_temp(char *name, t_data *data);
char	*get_env_check_envp(char *name, t_data *data);

/*----    CLI    ----*/
char	*cli(t_data *data);

/*----    Signal handling    ----*/
void	signal_handler(int signum);
void	signals_init(void);

/*----    Lexer    ----*/
t_lex_cmd	*lexer(char *cmd, t_data *data, t_executor *pt);
int		token_length(char *cmd);
int		fill_token_chain(char *command, t_data *data);
int		type_token_chain(t_data *data, t_executor *pt, t_lex_cmd *lc);
int		token_chain_analyzer(t_data *data, t_executor *pt);
int		analyze_redirections(t_data *data, t_executor *pt, t_lex_cmd *lc);
int		get_number_of_folders(char *path);
int		get_folders(char *path, char **folder_strs);
int		scan_folders(char **folder_strs, t_data *data);
int		allocate_for_binary(t_data *data);
void	type_token(t_token_chain *token_node, char *type);
int		is_builtin(char *token, t_data *data);
int		is_env_var(char *token);
int		is_last_pipe_exit(char *token);
int		is_var_decl(char *token, t_data *data);
int		check_for_env_vars(t_data *data, t_executor *pt);
int		check_for_binary_paths(t_data *data);
void	count_cmds(t_data *data);
int		count_slashes(const char *str);
void	expand_last_exit_status(t_token_chain *current);
void	cmd_space_trim(char *cmd);
int		no_space_tokens(char *cmd);
int		check_for_no_space_token(char *cmd);
int		number_of_tokens(char *cmd);
void	count_number_of_tokens(char **cmd, int *n, char *quote);
void	do_lesser(t_fill_t_c_data *ftcdata);
void	do_greater(t_fill_t_c_data *ftcdata);
void	pipe_less_gt(t_fill_t_c_data *ftcdata);
int		exec_data_preparation(t_data *data);
void	analyze_builtin(t_token_chain *current, t_data *data);

/*----    Executor    ----*/
int		executor(t_data *data, t_executor *pt);

/*----    Utils    ----*/
void	str_fill(char *to, char *from);
int		str_comp(const char *str1, const char *str2);
int		ft_strlen(const char *str);
char	*ft_memdup(const char *str);
void	*ft_memmove(void *dest, const void *src, size_t l);
char	*ft_join_path(const char *str1, const char *str2);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	**ft_split(char const *s, char c);
int		ft_contains_char(const char *str, char character);
int		tokens_len(t_token_chain *tokens);
void	init_folder_strs(char **folder_strs, int num_of_flds);
int		get_number_of_folders(char *path);
int		fpl(char *path);
int		check_exec_access(char *folder, struct dirent *dirent);
char	*ft_itoa(int n);
int		ft_atoi(const char *str);
int		last_slash(const char *str);

/*---- Debug utils ----*/
void	print_exec_data(t_exec *exec);
void	print_t_executor(t_executor *pt);

/*----	  Help		----*/
void	help(void);

char	*ft_strjoin_v(char const *s1, char const *s2);

#endif
