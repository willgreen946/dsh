#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <err.h>

#include "config.h"

int
config_print_prompt(void)
{
	char wd[256];

	if (!(getcwd(wd, 255))) {
		err(errno, "config_print_prompt");
		write(STDOUT_FILENO, ">", 1);
		return 1;
	}

	write(STDOUT_FILENO, wd, strlen(wd));
	write(STDOUT_FILENO, ">", 1);
	return (strlen(wd) + 1);
}
