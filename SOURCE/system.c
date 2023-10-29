#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>
#include <err.h>
#include <unistd.h>

#include "system.h"

void
sys_signal_handler(int sig)
{
	switch (sig) {
		case SIGINT:
			return;
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
	int return_value = 0;
	int child_status;
	pid_t child_pid;
	pid_t t_pid;

	if (!(child_pid = fork())) {
		return_value = execvp(argv[0], argv);
		/* FAIL */
		err(errno, "argv[0]");
		exit(EXIT_FAILURE);
	}

	else {
		/* Wait for the child process to terminate */
		do {
			t_pid = wait(&child_status);
			if (t_pid != child_pid)
				kill(t_pid, SIGTERM);
		} while (t_pid != child_pid);

		return return_value;
	}
}

/*
 * Sets the shell environment variable
 */
void
sys_set_shell(const char * shell)
{
	if (setenv("SHELL", shell, 1) == -1)
		err(errno, "sys_set_shell");
}
