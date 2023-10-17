#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include "sys.h"

/* Handles the execution and forks of processes */
int sys_execute(char *argv[]) {
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

/* Sets the SHELL enviroment variable */
void sys_change_shell(void) {
  if (setenv("SHELL", "dsh", 1) == -1)
    fprintf(stderr, "%s\n", strerror(errno));
}