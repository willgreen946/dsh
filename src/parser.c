#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "commands/commands.h"
#include "sys.h"

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

int parser_read_line(char *buf, size_t len) {
  char c;

  memset(buf, 0, strlen(buf));

  for (size_t i = 0; read(STDIN_FILENO, &c, 1); i++) {
    if (i > len)
      break;

    else if (c == '\n' || c == '\r')
      return 0;

    else
      *buf++ = c;
  }

  return 1;
}

int parser_line_parser(char *argv[]) {
  if (!strcmp(argv[0], "cd"))
    return cmd_cd(argv);

  else if (!strcmp(argv[0], "exit"))
    return cmd_exit(argv);

  return sys_execute(argv);
}