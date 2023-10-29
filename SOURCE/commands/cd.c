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
			err(errno, "cd");
			return EXIT_FAILURE;
		}

		if (chdir(home) == -1) {
			err(errno, "cd");
			return EXIT_FAILURE;
		}

		return 0;
	}

	else if (chdir(argv[1]) == -1) {
		err(errno, "cd");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
