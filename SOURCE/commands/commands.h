#ifndef __COMMANDS_H__
#define __COMMANDS_H__

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
 * The string refers the the command word, like "cd"
 * The function pointer refers to the function to be called
 */
struct COMMAND_MAP {
	const char *str;
	unsigned int(*fn)(const char **);
};

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
 * The map of built in shell commands
 */
struct COMMAND_MAP cmd_map[] = {
	{ "cd", cmd_cd },
	{ "cls", cmd_cls },
	{ "export", cmd_export },
	{ "exit", cmd_exit },
};

#include "cls.c"
#include "cd.c"
#include "export.c"
#include "exit.c"

#endif /* __COMMANDS_H__ */