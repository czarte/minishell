/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: voparkan <voparkan@student.42prague.cz>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 20:04:38 by voparkan          #+#    #+#             */
/*   Updated: 2024/07/06 20:04:38 by voparkan         ###   ########.fr       */
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

#define _POSIX_C_SOURCE 200809L

# include<stdio.h>
# include<stdlib.h>
# include<stdbool.h>
# include<readline/readline.h>
# include<readline/history.h>
# include<unistd.h>
# include<sys/wait.h>
# include<sys/stat.h>
# include<sys/types.h>
# include<signal.h>
# include<fcntl.h>
# include<dirent.h>
# include<libgen.h>
# include<sys/ioctl.h>
# include<termios.h>
# include<termcap.h>
# include"executor.h"

extern pid_t	pid;

typedef struct s_cmd_list t_cmd_list;
typedef struct s_token_chain t_token_chain;

typedef struct s_cmd_list{
	char		*cmd;
	char		*full_path;
	t_cmd_list	*next;
}	t_cmd_list;

/*
 type:
	pr	program
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
typedef struct s_token_chain{
	char			*token;
	char			type[3];
	t_token_chain	*next;
}	t_token_chain;

typedef struct s_exec_data{
	t_list	*cmd;			//command structured array
	char	*file[2];		//file paths
	bool	limit;			//delimiter flag
	bool	append;			//append flag
}	t_exec;

typedef struct s_data{
	t_cmd_list			*cmd_list;
	t_token_chain		*token_chain;
	t_cmd_list			*last_c_l_node;
	t_exec				*exec;
	char				**envp;
	char				**builtins;
	char				**local_temp_envp;
	char				work_dir[4096];
	char				prompt[66];
	int					n_cmd;
}	t_data;


/*----    Data functions    ----*/
int		data_init(t_data *data, char **envp);
int		exec_data_init(t_data *data);
int		free_data(t_data *data);
void	free_cmd_list(t_data *data);
void	free_token_chain(t_data *data);
void	free_exec(t_data *data);
void	free_folder_strs(char **folder_strs);
int		data_perror(t_data *data, char *msg);

/*----    Data preparation    ----*/
int		get_cmd_list(t_data *data);

/*----    Command functions    ----*/
char	*get_cmd_path(const char *cmd, t_data *data);
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
void	print_envp(char **envp);
char	*b_getenv(char *name, t_data *data);

/*----    CLI    ----*/
int		cli(t_data *data);

/*----    Signal handling    ----*/
void signal_handler(int signum);

/*----    Lexer    ----*/
int		lexer(char *cmd, t_data *data);
void	type_token_chain(t_data *data);
int		token_chain_analyzer(t_data *data);
int		get_number_of_folders(char *path);
int		get_folders(char *path, char **folder_strs);
int		scan_folders(char **folder_strs, t_data *data);
void	type_token(t_token_chain *token_node, char *type);

/*----    Executor    ----*/
int		executor(t_data *data);

/*----    Utils    ----*/
void	str_fill(char *to, char *from);
int		str_comp(const char *str1, const char *str2);
int		ft_strlen(const char *str);
char	*ft_memcpy(const char *str);
char	*ft_strjoin(const char *str1, const char *str2);
void	*ft_memcpy_o(void *dst, const void *src, size_t n);
char	**ft_split(char const *s, char c);
int		ft_contains_char(const char *str, char character);
int 	tokens_len(t_token_chain *tokens);

/*----	  Help		----*/
void    help();


#endif
