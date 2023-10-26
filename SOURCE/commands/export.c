#include "commands.h"

unsigned int
cmd_export(const char ** argv)
{
	size_t i;

	for (i = 0; argv[i]; i++)
		;

	if (i != 3) {
		write(STDERR_FILENO, "Export requires two arguments\n", 32);
		return 1;
	}

	if (setenv(argv[1], argv[2], 1)) {
		write(STDERR_FILENO, strerror(errno), strlen(strerror(errno)));
		write(STDERR_FILENO, "\n", 1);
		return errno;
	}

	return 0;
}