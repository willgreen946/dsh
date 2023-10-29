CC = pcc 
CFLAGS = -std=c89 -lc -Wall -Wextra -Werror -pedantic

all:
	$(CC) SOURCE/main.c $(CFLAGS) -O3 -o dsh

debug:
	$(CC) SOURCE/main.c $(CFLAGS) -g -o dsh
