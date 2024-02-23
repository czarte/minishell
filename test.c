#include<stdio.h>
#include<stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include<unistd.h>



/*READLINE LIBRARY TEST PROGRAM
gcc test.c -g -lreadline
*/
char	ft_str_match(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	return (1);
}

int main(void)
{
	char *line;

	line = NULL;
	while (1)
	{
		line = readline("Type something: ");
		printf("You typed: %s\n", line);
		if (ft_str_match(line, "exit"))
		{
			free(line);
			line = NULL;
			break ;
		}
		if (ft_str_match(line, "new line"))
			rl_on_new_line();
		if (ft_str_match(line, "replace0"))
		{
			rl_replace_line("What?? ", 0);
			rl_redisplay();
			usleep(500000);
		}
		if (ft_str_match(line, "replace1"))
		{
			rl_replace_line("What?? ", 1);
			rl_redisplay();
			usleep(500000);
		}
		if (ft_str_match("access existing", line))
		{
			if (access("info.txt", F_OK) == 0)
				printf("File info.txt exists!\n");
			else
				printf("File info.txt does not exist!\n");
		}
		if (ft_str_match("access nonexisting", line))
		{
			if (access("testicle", F_OK) == 0)
				printf("File testicle exists!\n");
			else
				printf("File testicle does not exist!\n");
		}
		if (line)
		{
			add_history(line);
			free(line);
			line = NULL;
		}
	}
	rl_clear_history();
	return (0);
}
