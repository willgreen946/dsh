#ifndef __COMMANDS_H__
#define __COMMANDS_H__

int return_value = 0;

/* Implementation of the cd command */
unsigned int cmd_cd(char *argv[]);

/* A command to exit the shell */
unsigned int cmd_exit(char *argv[]);

struct COMMAND_MAP {
 const char *str;
 unsigned int(*function)(char *argv[]);
};

struct COMMAND_MAP command_map[] = {
 { "cd", cmd_cd },
 { "exit", cmd_exit },
};

#include "exit.c"
#include "cd.c"

#endif /* __COMMANDS_H__ */