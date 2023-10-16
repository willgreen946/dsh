#include <stdlib.h>
#include <limits.h>

unsigned int dsh_exit(char *argv[]) {
 int ret = 0;

 if (!argv[1])
	exit(0);

 ret = (int)strtol(argv[1], NULL, 10);
 exit(ret);
}