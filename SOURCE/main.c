#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
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
 */
static void
dsh_raw_mode(void)
{
	struct termios raw;

	tcgetattr(STDIN_FILENO, &raw);

	/* Setting local flags (on) */
	raw.c_lflag &= (ECHO | ICRNL | ECHOE);

	/* Setting local flags (off) */
	raw.c_lflag &= ~(ICANON);

	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

/*
 * Returns new cursor position,
 * Prints backspace if current position is greater than the minimum
 */
static int
handle_backspace(int pos, int minimum_pos)
{
	if (pos > minimum_pos) {
		write(STDOUT_FILENO, (char*)0x7f, 0);
		return --pos;
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
			case 0x08:
				/* Fall through */
			case 0x7f:
				pos = handle_backspace(pos, prompt_len);
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
		fflush(stdout);

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

	/*return return_value;*/
}

static int
dsh_setup(void)
{
	/* Setting signal callback */
	signal(SIGINT, sys_signal_handler);

	/* Enter raw mode */
	dsh_raw_mode();

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
