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
}   t_cmd_list;

typedef struct s_data{
	t_cmd_list	*cmd_list;
	t_cmd_list	*last_c_l_node;
}   t_data;


/*----    Data functions    ----*/
int		data_init(t_data *data);
int		free_data(t_data *data);
void	free_cmd_list(t_data *data);
void	free_folder_strs(char **folder_strs);

/*----    Data preparation    ----*/
int	    get_cmd_list(t_data *data);

#endif
