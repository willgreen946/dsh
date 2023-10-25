#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include "config.h"

void
config_print_prompt(void)
{
	char wd[256];

	if (!(getcwd(wd, 255))) {
		fprintf(stderr, "%s\n", strerror(errno));
		fprintf(stdout, ">");
	}
	fprintf(stdout, "%s>", wd);
}