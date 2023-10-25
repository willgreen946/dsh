#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "system.h"
#include "parser.h"
#include "config.h"

/* Reads in a line from stdin */
/*static int
read_line(char * buf, size_t memcap)
{
	char c = (char)0;
	size_t cc;

	for (cc = 0; read(STDIN_FILENO, &c, 1); ++cc) {
		if (cc >= memcap)
			break;

		switch (c) {
			case '\n':*/
			/* Fall through */
			/*case '\r':
				return 0;
			default:
				*buf++ = c;
				break;
		}
	}*/
	/* Fail */
	/*return 1;
}*/

static int
event_loop(void)
{
	int return_value;
	char * argv[128];
	char buf[256];
	size_t i;

	for (;;) {
		config_print_prompt();

		if (fgets(buf, 255, stdin)) {
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
	sys_set_shell();
	return event_loop();
}

static int
parse_args(const char ** argv)
{
	if (!argv)
		{}
	return 0;
}

int
main(int argc, const char ** argv)
{
	return (argc < 2) ? dsh_setup() : parse_args(argv);
}