#include <ctype.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "commands/commands.h"
#include "config.h"
#include "parser.h"
#include "sys.h"

/* The main loop of the shell */
static int dsh_event_loop(void) {
  char buf[256], *argv[256];

  for (;;) {
		memset(buf, 0, strlen(buf));
    config_print_prompt();

		fflush(stdout);

    if (parser_read_line(buf, 255))
      fprintf(stderr, "ERROR: taking input\n");

    else {
      parser_rm_newline(buf);
      parser_line_splitter(argv, buf, 255);

      if (argv[0])
        return_value = parser_line_parser(argv);

      /* Reset argv */
      for (size_t i = 0; argv[i]; i++)
        memset(argv[i], 0, strlen(argv[i]));
    }
  }

  return 0;
}

static int dsh_setup(void) {
  sys_change_shell();
  dsh_event_loop();
  return 0;
}

/* TODO make this run shell files */
static int dsh_parse_args(const char **argv) {
  if (!argv)
    return 1;
  return 0;
}

int main(int argc, const char **argv) {
  return (argc < 2) ? dsh_setup() : dsh_parse_args(argv);
}