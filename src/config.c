#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "config.h"

void config_print_prompt(void) {
  char working_directory[256];

  if (!(getcwd(working_directory, 255))) {
    fprintf(stderr, "%s\n", strerror(errno));
    fprintf(stdout, ">");
  }

  fprintf(stdout, "%s>", working_directory);
}

char *config_prompt(void) {
  char *wd = (char*)malloc(256);

  if (!(getcwd(wd, 255))) {
    fprintf(stderr, "%s\n", strerror(errno));
    return ">";
  }

	strncat(wd, ">", 2);
	return wd;
}