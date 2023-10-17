#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "config.h"

void dsh_config_print_prompt(void) {
  char working_directory[256];

  if (!(getcwd(working_directory, 255))) {
    fprintf(stderr, "%s\n", strerror(errno));
    fprintf(stdout, ">");
  }

  fprintf(stdout, "%s>", working_directory);
}