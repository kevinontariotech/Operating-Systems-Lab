#include "myshell.h"
#define MAXPATH 1024

int cd(char **args);
int clr(char **args);
int dir(char **args);
int env(char **args);
int echo(char **args);
int help(char **args);
int paus(char **args);
int quit(char **args);

char *commands[] = {
    "cd", "clr", "dir", "env", "echo", "help", "paus", "quit"
};

int (*command_func[])(char **) = {
    &cd, &clr, &dir, &env, &echo, &help, &paus, &quit
};

int num_command(){
    return sizeof(commands) / sizeof(char *);
}

//implementation of the shell commands
int cd(char **args){
    if (args[1] == NULL){
        printf("shell is expecting an argument");
    } else {
        if (chdir(args[1]) != 0){
            perror("No such directory");
        }
    }

    return 1;
}

int clr(char **args){
    system("clear");
    return 1;
}

int dir(char **args){
    DIR *d;
    struct dirent *dir;
    d = opendir(".");

    if (d) {
        while ((dir = readdir(d)) != NULL) {
            printf("%s\n", dir->d_name);
        }
        closedir(d);
    }

    return 1;
}

int env(char **args){

    char ** env = environ;

    while (*env){
        printf("%s\n", *env++);
    }

    return 1;
}

int echo(char **args){

    while (*args){
        printf("%s ", *args++);
    }
    printf("\n");
    
    return 1;
}

int help(char **args){

    printf("This is an example shell");
    printf("These are the commands that are imlemented");

    for (int i = 0; i < num_command(); i++){
        printf(" - %s\n", commands[i]);
    }

    return 1;
}

int paus(char **args){

    printf("Paused: press ENTER to continue");
    getchar();

    return 1;
}

int quit(char **args){
    return 0;
}
