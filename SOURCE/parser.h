#ifndef __PARSER_H__
#define __PARSER_H__

#include <stdlib.h>
#include <string.h>

#include "commands/commands.h"

/*
 * Removes newlines from a string
 */
void parse_rm_newline(char *);

/*
 * Evaluates the line and sends it off to be executed
 */
int parse_line(char **);

/*
 * Splits up line by the delim char (const char *)
 * size_t is used to indicate the maximum elements in (char **)
 * (char *) is the original string that we want to split up
 * The splits will be placed in the array (char **)
 */
void parse_line_splitter(char **, char *, const char *, size_t);

#include "parser.c"

#endif /* __PARSER_H__ */
