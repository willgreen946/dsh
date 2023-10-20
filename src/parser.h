#ifndef __PARSER_H__
#define __PARSER_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "sys.h"

/* Reads a line of input from stdin */
int parser_read_line(char *buf, size_t len);

/* Creates context out of argv[] */
int parser_line_parser(char *argv[]);

/* Splits up line of input by whitespace and places words into argv[] */
void parser_line_splitter(char *argv[], char *str, size_t array_size);

/* Removes newline chars from a string */
void parser_rm_newline(char *buf);

#include "parser.c"

#endif /* __PARSER_H__ */