#ifndef __CONFIG_H__
#define __CONFIG_H__

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

unsigned int prompt_len = 0;

/*
 * Prints the prompt to stdout
 */
int config_print_prompt(void);

#include "config.c"

#endif /* __CONFIG_H__ */
