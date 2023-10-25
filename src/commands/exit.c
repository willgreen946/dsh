#include "commands.h"

/*
 * Exits out of the shell
 */
unsigned int
cmd_exit(const char ** argv)
{
	int return_value = 0;

	if (argv[1]) {
		return_value = (int)strtol(argv[1], (char**)NULL, 10);
		exit(return_value);
	}

	exit(0);
	return return_value;
}