#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "commands/commands.h"
#include "sys.h"

typedef enum {
	BACKSPACE = 127,
}KEY_CODES;

/* Splits up line by whitespace and places them in argv[] */
void parser_line_splitter(char *argv[], char *str, size_t array_size) {
  char **p_argv;

  for (p_argv = argv; (*p_argv = strsep(&str, " \t"));) {
    if (**p_argv)
      if (++p_argv >= &argv[array_size])
        break;
  }
}

/* Removes newline chars from a string */
void parser_rm_newline(char *buf) {
  char *p_buf;

  if ((p_buf = strchr(buf, '\n')))
    *p_buf = (char)0;
}

int parser_line_parser(char *argv[]) {
	int ret = 0;

	/* Check for built in shell commands */
	if ((ret = sys_find_native(argv)) >= 0)
		return command_map[ret].function(argv);

  return sys_execute(argv);
}