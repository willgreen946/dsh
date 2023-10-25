#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>

/*
 * Handles signals passed to the program
 */
void sys_signal_handler(int);

/*
 * executes a command from the argv array (char **)
 */
int sys_execute(char **);

/*
 * Sets the shell environment variable
 */
void sys_set_shell(void);

#include "system.c"

#endif /* __SYSTEM_H__ */