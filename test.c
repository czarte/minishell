#include<stdio.h>
#include<stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>



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
		if (line)
		{
			free(line);
			line = NULL;
		}
	}
	rl_clear_history();
	return (0);
}
