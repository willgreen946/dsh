CC=gcc

all:
	$(CC) src/main.c -o dsh -Wall -Wextra -pedantic -O3
