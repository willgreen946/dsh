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
			fprintf(stderr, "%s\n", strerror(errno));
			return errno;
		}

		if (chdir(home) == -1) {
			fprintf(stderr, "%s\n", strerror(errno));
			return errno;
		}

		return 0;
	}

	else if (chdir(argv[1]) == -1) {
		fprintf(stderr, "%s\n", strerror(errno));
		return errno;
	}

	return 0;
}