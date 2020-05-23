#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

struct termios orig_termios;

void disableRaw(void) {
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRaw(void) {
	tcgetattr(STDIN_FILENO, &orig_termios);
	atexit(disableRaw);
	struct termios raw = orig_termios;
	raw.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int main(void) {
	enableRaw();
	
	char c;
	while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q') {
		if (iscntrl(c)) {
			printf("%d\n", c);
		} else {
			printf("%d ('%c')\n", c, c);
		}
	}

	return 0;
}
