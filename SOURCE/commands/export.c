#include "commands.h"

unsigned int
cmd_export(const char ** argv)
{
	size_t i;

	for (i = 0; argv[i]; i++)
		;

	if (i != 3) {
		err(EXIT_FAILURE, "requires two arguments\n");
		return 1;
	}

	if (setenv(argv[1], argv[2], 1)) {
		err(errno, "export");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
