/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 01:35:17 by smelicha          #+#    #+#             */
/*   Updated: 2024/04/06 23:00:06 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include<stdio.h>
# include<stdlib.h>
# include<readline/readline.h>
# include<readline/history.h>
# include<unistd.h>
# include<sys/wait.h>
# include<sys/stat.h>
# include<signal.h>
# include<fcntl.h>
# include<dirent.h>
# include<sys/ioctl.h>
# include<termios.h>
# include<termcap.h>

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
	pi	pipe				|
	ri	redirect input		<
	ro	redirect output		>
	rd	redirect delimiter	<<
	ra	redirect append		>>
	ev	environment var		$something
	es	last pi ex. stat.	$?
 */
typedef struct s_token_chain{
	char			*token;
	char			type[3];
	t_token_chain	*next;
}	t_token_chain;

typedef struct s_data{
	t_cmd_list	*cmd_list;
	t_token_chain	*token_chain;
	t_cmd_list	*last_c_l_node;
	char		**envp;
	char		**builtins;
	char		work_dir[4096];
	char		prompt[66];
}	t_data;

/*----    Data functions    ----*/
int		data_init(t_data *data, char **envp);
int		free_data(t_data *data);
void	free_cmd_list(t_data *data);
void	free_token_chain(t_data *data);
void	free_folder_strs(char **folder_strs);

/*----    Data preparation    ----*/
int		get_cmd_list(t_data *data);

/*----    Command functions    ----*/
char	*get_cmd_path(const char *cmd, t_data *data);

/*----    Builtin commands functions    ----*/
void	cd(const char *new_wd, t_data *data);
void	echo(t_token_chain *echo_tok);
int		env(t_token_chain *current, t_data *data);

/*----    CLI    ----*/
int		cli(t_data *data);

/*----    Lexer    ----*/
int		lexer(char *cmd, t_data *data);
void	type_token_chain(t_data *data);
int		token_chain_analyzer(t_data *data);

/*----    Executer    ----*/
int		executer(t_data *data);

/*----    Utils    ----*/
void	str_fill(char *to, char *from);
int		str_comp(const char *str1, const char *str2);
int		ft_strlen(const char *str);
char	*ft_memcpy(const char *str);
char	*ft_strjoin(const char *str1, const char *str2);

#endif
