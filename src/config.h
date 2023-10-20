#ifndef __CONFIG_H__
#define __CONFIG_H__

/* Prints the shell prompt to stdout */
void config_print_prompt(void);

char *config_prompt(void);

#include "config.c"

#endif /* __CONFIG_H__ */