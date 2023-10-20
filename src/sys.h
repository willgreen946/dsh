#ifndef __SYS_H__
#define __SYS_H__

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

#include "commands/commands.h"

/* Handles execution of programs and forks */
int sys_execute(char *argv[]);

/* Returns index of native (built in) shell command
 * see commands/commands.h for the list */
ssize_t sys_find_native(char *argv[]);

/* Changes the SHELL environment variable */
void sys_change_shell(void);

#include "sys.c"
#endif /* __SYS_H__ */