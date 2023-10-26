CC = gcc

all:
	$(CC) SOURCE/main.c -std=c89 -Wall -Wextra -Werror -pedantic -O3 -o dsh
debug:
	$(CC) SOURCE/main.c -std=c89 -Wall -Wextra -pedantic -g -o dsh
