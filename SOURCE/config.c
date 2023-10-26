#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include "config.h"

int
config_print_prompt(void)
{
	char wd[256];

	if (!(getcwd(wd, 255))) {
		write(STDERR_FILENO, strerror(errno), strlen(strerror(errno)));
		write(STDERR_FILENO, "\n", 1);
		write(STDOUT_FILENO, ">", 1);
		return 1;
	}

	write(STDOUT_FILENO, wd, strlen(wd));
	write(STDOUT_FILENO, ">", 1);
	return (strlen(wd) + 1);
}