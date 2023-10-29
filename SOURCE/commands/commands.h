#ifndef __COMMANDS_H__
#define __COMMANDS_H__

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <err.h>

#ifndef EXIT_FAILURE
	#define EXIT_FAILURE 1
#endif /* EXIT_FAILURE */

#ifndef EXIT_SUCCESS
	#define EXIT_SUCCESS 0
#endif /* EXIT_SUCCESS */

/*
 * Exports environment variable
 */
unsigned int cmd_export(const char **);

/*
 * Clears the screen
 */
unsigned int cmd_cls(const char **);

/*
 * Changes the current working directory
 */
unsigned int cmd_cd(const char **);

/*
 *	Exits the shell
 */
unsigned int cmd_exit(const char **);

/*
 * The string refers the the command word, like "cd"
 * The function pointer refers to the function to be called
 */
struct COMMAND_MAP {
	const char * str;
	unsigned int(*fn)(const char **);
	const size_t len;
};

/*
 * Maximum amount of commands in struct
 */
#define CMD_MAX 4

/*
 * The map of built in shell commands
 */
struct COMMAND_MAP cmd_map[CMD_MAX] = {
	{ "cd", cmd_cd, 2 },
	{ "cls", cmd_cls, 3},
	{ "export", cmd_export, 6},
	{ "exit", cmd_exit, 4 },
};

#include "cls.c"
#include "cd.c"
#include "export.c"
#include "exit.c"

#endif /* __COMMANDS_H__ */
