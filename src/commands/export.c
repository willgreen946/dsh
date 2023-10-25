#include "commands.h"

unsigned int
cmd_export(const char ** argv)
{
	size_t i;

	for (i = 0; argv[i]; i++)
		;

	if (i != 3) {
		fprintf(stderr, "Export requires two arguments\n");
		return 1;
	}

	if (setenv(argv[1], argv[2], 1)) {
		fprintf(stderr, "%s\n", strerror(errno));
		return errno;
	}

	return 0;
}