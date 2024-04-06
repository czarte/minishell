/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 01:35:17 by smelicha          #+#    #+#             */
/*   Updated: 2024/04/06 20:59:34 by smelicha         ###   ########.fr       */
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

typedef struct s_cmd_list{
	char		*cmd;
	char		*full_path;
	t_cmd_list	*next;
}	t_cmd_list;

typedef struct s_data{
	t_cmd_list	*cmd_list;
	t_cmd_list	*last_c_l_node;
	char		work_dir[4096];
	char		prompt[66];
}	t_data;


/*----    Data functions    ----*/
int		data_init(t_data *data);
int		free_data(t_data *data);
void	free_cmd_list(t_data *data);
void	free_folder_strs(char **folder_strs);

/*----    Data preparation    ----*/
int	    get_cmd_list(t_data *data);

/*----    Command functions    ----*/
char	*get_cmd_path(const char *cmd, t_data *data);

/*----    Builtin commands functions    ----*/
void	cd(const char *new_wd, t_data *data);

/*----    CLI    ----*/
int		cli(t_data *data);

/*----    Utils    ----*/
int		str_comp(const char *str1, const char *str2);
int		ft_strlen(const char *str);

#endif
