#ifndef __SYS_H__
#define __SYS_H__

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

/* Handles execution of programs and forks */
int sys_execute(char *argv[]);

/* Changes the SHELL environment variable */
void sys_change_shell(void);

#include "sys.c"
#endif /* __SYS_H__ */