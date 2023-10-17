#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

unsigned int cmd_cd(char *argv[]) {
 const char *home;

 if (!argv[1]) {
	if (!(home = getenv("HOME"))) {
	 fprintf(stderr, "%s\n", strerror(errno));
	 return errno;
	}

	if (chdir(home) == -1) {
	 fprintf(stderr, "%s\n", strerror(errno));
	 return errno;
	}

	return 0;
 }

 else if (chdir(argv[1]) == -1) {
	fprintf(stderr, "%s\n", strerror(errno));
	return errno;
 }

 return 0;
}