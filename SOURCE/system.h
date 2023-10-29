#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>
#include <err.h>
#include <unistd.h>

#ifndef EXIT_FAILURE
	#define EXIT_FAILURE 1
#endif /* EXIT_FAILURE */

#ifndef EXIT_SUCCESS
	#define EXIT_SUCCESS 0
#endif /* EXIT_SUCCESS */

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
void sys_set_shell(const char * shell);

#include "system.c"

#endif /* __SYSTEM_H__ */
