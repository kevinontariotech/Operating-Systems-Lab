#ifndef MY_SHELL
#define MY_SHELL

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include "string.h"
#include <sys/wait.h>
#include <dirent.h>

#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"
#define _POSIX_SOURCE

extern char **environ;

void main_loop();
char *readline(void);
char **tokenize(char *line);
int execute(char **args);
int launch(char **args);

#endif