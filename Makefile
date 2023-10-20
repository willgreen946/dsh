CC=gcc

all:
	$(CC) src/main.c -o dsh -lreadline -Wall -Werror -Wextra -pedantic -O3
