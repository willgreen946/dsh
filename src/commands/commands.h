#ifndef __COMMANDS_H__
#define __COMMANDS_H__

int return_value = 0;

/* Implementation of the cd command */
unsigned int dsh_cd(char *argv[]);

/* A command to exit the shell */
unsigned int dsh_exit(char *argv[]);

struct COMMAND_MAP {
 const char *command;
 unsigned int(*function)(char *argv[]);
};

struct COMMAND_MAP command_map[] = {
 { "cd", dsh_cd },
 { "exit", dsh_exit },
};

#include "exit.c"
#include "cd.c"

#endif /* __COMMANDS_H__ */