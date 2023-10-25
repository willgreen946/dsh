#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>

#include "system.h"

void
sys_signal_handler(int sig)
{
	switch (sig) {
		default:
			break;
	}
}

/*
 * executes a command from the argv array (char **)
 */
int
sys_execute(char ** argv)
{
	int child_status;
	pid_t child_pid;
	pid_t t_pid;

	if (!(child_pid = fork())) {
		execvp(argv[0], argv);
		/* FAIL */
		fprintf(stderr, "%s:Unkown command\n", argv[0]);
		exit(1);
	}

	else {
		/* Wait for the child process to terminate */
		do {
			t_pid = wait(&child_status);
			if (t_pid != child_pid)
				kill(t_pid, SIGTERM);
		} while (t_pid != child_pid);

		return child_pid;
	}
}

/*
 * Sets the shell environment variable
 */
void
sys_set_shell(void)
{
	if (setenv("SHELL", "dsh", 1) == -1)
		fprintf(stderr, "\n%s\n", strerror(errno));
}