#ifndef MY_SHELL
#define MY_SHELL

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include "string.h"
#include <sys/wait.h>

#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"
#define _POSIX_SOURCE

void lsh_loop();
char *lsh_read_line(void);
char **lsh_split_line(char *line);
int lsh_launch(char **args);

#endif