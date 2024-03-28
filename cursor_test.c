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

int main() {
    char buf[1024]; // Buffer to store terminal information

    // Get terminal information for "xterm" terminal type
    if (tgetent(buf, "xterm") != 1) {
        fprintf(stderr, "Error getting terminal information\n");
        return 1;
    }

    // Get the cursor motion capability
    char *cursor_motion = tgetstr("cm", NULL);
    if (cursor_motion == NULL) {
        fprintf(stderr, "Cursor motion capability not available.\n");
        return 1;
    }

    // Use tgoto to construct cursor motion string to move to (5, 10)
    int col = 5;
    int row = 10;
    char *cursor_move = tgoto(cursor_motion, col, row);
    if (cursor_move == NULL) {
        fprintf(stderr, "Error constructing cursor motion string.\n");
        return 1;
    }

    // Print the constructed cursor motion string
    printf("Cursor motion string to move to (%d, %d): %s\n", col, row, cursor_move);

    return 0;
}
