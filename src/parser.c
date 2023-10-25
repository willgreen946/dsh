#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "commands/commands.h"
#include "system.h"
#include "parser.h"

/*
 * Removes newline character(s) from a string
 */
void
parse_rm_newline(char * buf)
{
	char *p_buf;

	if ((p_buf = strchr(buf, '\n')))
		*p_buf = (char)0;
}

int
parse_line(char ** argv)
{
	char var[256];
	char * val;
	size_t i;
	size_t k;

	/* Check for variables */
	for (i = 0; argv[i]; i++) {
		if (argv[i][0] == '$') {
			for (k = 1; argv[i][k]; k++)
				strncat(var, &argv[i][k], 1);

			if (!(val = getenv(var)))
				argv[i] = strncpy(argv[i], "NULL", 5);

			else
				argv[i] = strncpy(argv[i], val, 255);

			memset(var, 0, strlen(var));
		}
	}

	/* Check for built in commands */
	for (i = 0; cmd_map[i].str; i++)
		if (!strncmp(cmd_map[i].str, argv[0], strlen(argv[0])))
			return cmd_map[i].fn((const char **)argv);

	return sys_execute(argv);
}

void
parse_line_splitter(char ** argv, char * str, const char * delim, size_t max) 
{
	char ** p_argv;

	for (p_argv = argv; (*p_argv = strsep(&str, delim));)
		if (**p_argv)
			if (++p_argv >= &argv[max])
				break;
}
