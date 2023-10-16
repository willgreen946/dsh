#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

#include "commands/commands.h"
#include "config.h"

/* Splits up a line of input by whitespace and places words in argv array */
static void dsh_line_splitter(char *argv[], char *str, size_t array_size) {
 char **p_argv;

 for (p_argv = argv; (*p_argv = strsep(&str, " \t"));) {
	if (**p_argv)
	 if (++p_argv >= &argv[array_size])
		break;
 }
}

/* Remove newline char from a string */
static void dsh_rm_newline(char *buf) {
 char *p_buf;

 if ((p_buf = strchr(buf, '\n')))
	*p_buf = (char)0;
}

/* Handles the execution of processes */
static int dsh_execute(char *argv[]) {
 int child_status;
 pid_t child_pid, t_pid;

 if (!(child_pid = fork())) {
	execvp(argv[0], argv);
	/* FAIL */
	fprintf(stderr, "%s: Unknown command\n", argv[0]);
	exit(0);
 }

 else {
	/* Wait for the child to terminate */
	do {
	 t_pid = wait(&child_status);
	 if (t_pid != child_pid)
		kill(t_pid, SIGTERM);
	} while (t_pid != child_pid);

	return child_pid;
 }
}

/* Sees if argv[0] is a built in command */
static int dsh_built_in(char *argv[]) {
 for (size_t i = 0; command_map[i].command; i++) {
	if (!strcmp(argv[0], command_map[i].command))
	 return command_map[i].function(argv);
 }
 return -1;
}

/* TODO handle pipes */
static int dsh_line_parser(char *argv[]) {
 int ret = 0;

 /*if ((ret = dsh_built_in(argv)) != -1)
	return ret;*/

 if (!strcmp(argv[0], "cd"))
	dsh_cd(argv);

 else if (!strcmp(argv[0], "exit"))
	dsh_exit(argv);

 return dsh_execute(argv);
}

/* The main loop of the shell */
static int dsh_event_loop(void) {
 char buf[256], *argv[256];

 for (;;) {
	dsh_config_print_prompt();

	if (!fgets(buf, 255, stdin))
	 fprintf(stderr, "%s\n", strerror(errno));

	else {
	 dsh_rm_newline(buf);
	 dsh_line_splitter(argv, buf, 255);

	 if (argv[0])
		return_value = dsh_line_parser(argv);
	}
 }
 return 0;
}

/* TODO make this run shell files */
static int dsh_parse_args(const char **argv) {
 if (!argv) return 1;

 return 0;
}

int main(int argc, const char **argv) {
 return (argc < 2) ? dsh_event_loop() : dsh_parse_args(argv);
}