#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <err.h>

#include "system.h"
#include "parser.h"
#include "config.h"

#ifndef EXIT_FAILURE
	#define EXIT_FAILURE 1
#endif /* EXIT_FAILURE */

#ifndef EXIT_SUCCESS
	#define EXIT_SUCCESS 0
#endif /* EXIT_SUCCESS */

/*
 * Takes the terminal out of canonical mode
 * (cooked) and enters into raw mode
 * look in termios man page for details on,
 * individual flags
 */
static int 
dsh_raw_mode(void)
{
	struct termios raw;

	if (tcgetattr(STDIN_FILENO, &raw) < 0) {
		err(errno, "dsh_raw_mode");
		return EXIT_FAILURE;
	}

	/* Setting local flags (on) */
	raw.c_lflag &= (ICRNL 
		| ECHO | ECHONL | ECHOE | ECHOPRT);

	/* Setting local flags (off) */
	raw.c_lflag &= ~(ICANON | ECHOCTL | ISIG | IEXTEN);

	/* Setting output flags (off) */
	raw.c_oflag &= ~(OXTABS);

	/* 1 byte enough to return from read() */	
	raw.c_cc[VMIN] = 1;
	raw.c_cc[VTIME] = 0;

	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) < 0) {
		err(errno, "dsh_raw_mode");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

/*
 * Returns new cursor position,
 * Prints backspace if current position is greater than the minimum
 */
static int
dsh_backspace(int pos, int minimum_pos)
{
	if (pos > minimum_pos) {
		write(STDOUT_FILENO, (char*)VERASE, 0);
		return pos - 1;
	}
	return pos;
}

/*
 * Reads in a line from stdin with unistd read()
 * Certain chars will invoke different reactions
 * For example \b will move the cursor back one space
 */
static int
dsh_read_line(char * buf, size_t memcap)
{
	size_t cc;
	ssize_t ret;
	char c = (char)0;
	int pos = prompt_len;

	memset(buf, 0, strlen(buf));

	for (cc = 0; (ret = read(STDIN_FILENO, &c, 1)); ++cc) {
		if (ret < 0) {
			err(errno, "dsh_read_line");
			return EXIT_FAILURE;
		}

		if (cc >= memcap)
			break;

		switch (c) {
			case EOF:
			/* Fall through */
			case '\n':
			/* Fall through */
			case '\r':
				*buf = (char)0;
				return EXIT_SUCCESS;
			case VERASE:
			/* Fall through */
			case VWERASE:
			/* Fall through */
			case 0x08:
			/* Fall through */
			case 0x7f:
				pos = dsh_backspace(pos, prompt_len);
				*buf-- = (char)0;
				break;
			default:
				*buf++ = c;
				*buf = (char)0;
				pos++;
				break;
		}
	}

	/* Fail */
	err(EXIT_FAILURE, "Input too long");
	return EXIT_FAILURE;
}

static int
dsh_event_loop(void)
{
	int return_value;
	char * argv[128];
	char buf[512];
	size_t i;

	for (;;) {
		prompt_len = config_print_prompt();

		if (!dsh_read_line(buf, 511)) {
			parse_rm_newline(buf);
			parse_line_splitter((char**)argv, buf, " \t", 128);

			if (*argv)
				return_value = parse_line((char**)argv);

			/* Clear the argv array */
			for (i = 0; argv[i]; i++)
				memset(argv[i], 0, strlen(argv[i]));
		}
	}

	return return_value;
}

static int
dsh_setup(void)
{
	/* Enter raw mode */
	if (dsh_raw_mode())
		return EXIT_FAILURE;

	/* Set the shell environment variable */
	sys_set_shell("DSH");

	/* Enter into the main loop */
	return dsh_event_loop();
}

static int
dsh_parse_args(const char ** argv)
{
	if (!argv)
		{}
	return EXIT_SUCCESS;
}

int
main(int argc, const char ** argv)
{
	return (argc < 2) ? dsh_setup() : dsh_parse_args(argv);
}
