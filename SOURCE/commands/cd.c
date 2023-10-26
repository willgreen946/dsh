#include "commands.h"

/*
 * Changes the current working directory
 */
unsigned int
cmd_cd(const char ** argv)
{
	const char * home;

	/* No arguments */
	if (!argv[1]) {
		if (!(home = getenv("HOME"))) {
			write(STDERR_FILENO, strerror(errno), strlen(strerror(errno)));
			write(STDERR_FILENO, "\n", 1);
			return errno;
		}

		if (chdir(home) == -1) {
			write(STDERR_FILENO, strerror(errno), strlen(strerror(errno)));
			write(STDERR_FILENO, "\n", 1);
			return errno;
		}

		return 0;
	}

	else if (chdir(argv[1]) == -1) {
		write(STDERR_FILENO, strerror(errno), strlen(strerror(errno)));
		write(STDERR_FILENO, "\n", 1);
		return errno;
	}

	return 0;
}