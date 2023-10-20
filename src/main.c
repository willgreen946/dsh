#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "commands/commands.h"
#include "config.h"
#include "parser.h"
#include "sys.h"

/* The main loop of the shell */
static int dsh_event_loop(void) {
  char *argv[256], *line = NULL, *prompt = NULL;

  for (;;) {
		prompt = config_prompt();

		if (!(line = readline(prompt))) {} /* Do nothing */

    else {
			add_history(line);
			parser_line_splitter(argv, line, 255);

      if (argv[0])
        return_value = parser_line_parser(argv);

      /* Reset argv */
      for (size_t i = 0; argv[i]; i++)
        memset(argv[i], 0, strlen(argv[i]));

			free(line);
			free(prompt);
    }
  }

  return 0;
}

static int dsh_setup(void) {
	/* Change $SHELL */
  sys_change_shell();

	/* Enable tab complete */
	rl_bind_key('\t', rl_complete);
	using_history();
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