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

bool	forbidden_cahracters(char *var)
{
	while (*var)
	{
		if ((('A' <= *var) && ('Z' >= *var))
				|| (('a' <= *var) && ('z' >= *var))
				|| (('0' <= *var) && ('9' >= *var))
				|| *var == '_' || *var == '=')
			var++;
		else
			return true;
	}
	return false;
}

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

int main() {
    char *buf; // Buffer to store terminal information

    // // Get terminal information for "xterm" terminal type
    // if (tgetent(buf, "xterm") != 1) {
    //     fprintf(stderr, "Error getting terminal information\n");
    //     return 1;
    // }
    //
    // // Get the cursor motion capability
    // char *cursor_motion = tgetstr("cm", NULL);
    // if (cursor_motion == NULL) {
    //     fprintf(stderr, "Cursor motion capability not available.\n");
    //     return 1;
    // }
    //
    // // Use tgoto to construct cursor motion string to move to (5, 10)
    // int col = 5;
    // int row = 10;
    // char *cursor_move = tgoto(cursor_motion, col, row);
    // if (cursor_move == NULL) {
    //     fprintf(stderr, "Error constructing cursor motion string.\n");
    //     return 1;
    // }
    //
    // // Print the constructed cursor motion string
    // printf("Cursor motion string to move to (%d, %d): %s\n", col, row, cursor_move);

    buf = ft_memdup("ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890abcdefghijklmnopqrstuvwxzy_=");
	printf("%d %s\n", forbidden_cahracters(buf), buf);
	free(buf);
	buf = ft_memdup("@ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890abcdefghijklmnopqrstuvwxzy_=");
	printf("%d %s\n", forbidden_cahracters(buf), buf);
	free(buf);
    return 0;
}
