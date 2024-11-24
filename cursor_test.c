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


int main() {
    char *buf; // Buffer to store terminal information


    buf = ft_memdup("-\"100\"");
	printf("|%s|\n", buf);
	remove_chars(buf, "\"\'");
	printf("|%s|\n\n", buf);
	free(buf);
}
