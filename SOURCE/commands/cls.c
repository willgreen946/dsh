#include "commands.h"

unsigned int
cmd_cls(const char ** argv)
{
	const char * CLEAR = "\033[H\033[J";

	if (!argv) {} /* To silence warnings */

	write(STDOUT_FILENO, CLEAR, 12);
	return 0;
}