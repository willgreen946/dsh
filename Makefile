CC = gcc

all:
	$(CC) src/main.c -std=c89 -Wall -Wextra -Werror -pedantic -O3 -o dsh
debug:
	$(CC) src/main.c -std=c89 -Wall -Wextra -pedantic -g -o dsh
