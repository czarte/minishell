#include<stdio.h>
#include<stdlib.h>
#include<readline/readline.h>
#include<readline/history.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<signal.h>
#include<fcntl.h>
#include<dirent.h>
#include<sys/ioctl.h>
#include<termios.h>
#include<ncurses.h>
#include<termcap.h>

char	*ft_memdup(const char *str)
{
	char	*cpy;
	int		i;

	cpy = NULL;
	i = 0;
	if (!str)
		return (NULL);
	cpy = malloc(sizeof(char) * (strlen(str) + 1));
	if (!cpy)
		return (NULL);
	while (str[i])
	{
		cpy[i] = str[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

bool	check_char(char c, char *chars)
{
	int	char_i;

	char_i = 0;
	while (chars[char_i])
	{
		if (c == chars[char_i])
			return (true);
		char_i++;
	}
	return (false);
}

void	remove_chars(char *str, char *chars)
{
	int	str_i;
	int	cpy_i;

	if (!str)
		return ;
	str_i = 0;
	cpy_i = 0;
	while (str[str_i])
	{
		if (!check_char(str[str_i], chars))
			str[cpy_i++] = str[str_i];
		str_i++;
	}
	str[cpy_i] = '\0';
}


bool	forbidden_cahracters(char *var)
{
	char	*tmp_var;

	tmp_var = var;
	printf("from forbidden char test: |%s|\n", tmp_var);
	if (!var)
		return (false);
	while (1)
	{
		if (*var == '=' && var != tmp_var)
			return (false);
		if ((('A' <= *var) && ('Z' >= *var))
			&& (('a' <= *var) && ('z' >= *var))
			&& (('0' <= *var) && ('9' >= *var))
			&& *var == '_' && *var != '\0')
			var++;
		else
		{
			printf("forbidden found\n");
			return (true);
		}
	}
	return (false);
}

int main() {
    char *buf; // Buffer to store terminal information


    buf = ft_memdup("AHOJ");
	printf("|%s|\n", buf);
	forbidden_cahracters(buf);
	free(buf);
	buf = ft_memdup("@HOJ");
	printf("|%s|\n", buf);
	forbidden_cahracters(buf);
	free(buf);
}
