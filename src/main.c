#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <ctype.h>
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

/* TODO handle pipes */
static int dsh_line_parser(char *argv[]) {
 if (!strcmp(argv[0], "cd"))
	return dsh_cd(argv);

 else if (!strcmp(argv[0], "exit"))
	return dsh_exit(argv);

 return dsh_execute(argv);
}

/* Sets the SHELL enviroment variable */
static void dsh_change_shell(void) {
 if (setenv("SHELL", "dsh", 1) == -1)
	fprintf(stderr, "%s\n", strerror(errno));
}

static int dsh_read_line(char *buf, size_t len) {
 char c;

 memset(buf, 0, strlen(buf));

 for (size_t i = 0; read(STDIN_FILENO, &c, 1); i++) {
	if (i > len)
	 break;

	if (c == '\n' || c == '\r') {
	 return 0;
	}

	*buf++ = c;
 }

 return 1;
}

/* The main loop of the shell */
static int dsh_event_loop(void) {
 char buf[256], *argv[256];

 dsh_change_shell();

 for (;;) {
	dsh_config_print_prompt();

	if (dsh_read_line(buf, 255) != 0)
	 fprintf(stderr, "ERROR: taking input\n");

	else {
	 dsh_rm_newline(buf);
	 dsh_line_splitter(argv, buf, 255);

	 if (argv[0]) {
		return_value = dsh_line_parser(argv);
	 }

		/* Reset argv */
		for (size_t i = 0; argv[i]; i++) {
		 memset(argv[i], 0, strlen(argv[i]));
		}

		fflush(stdout);
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