#include "myshell.h"

int main(int argc, char **argv)
{
  // Load config files, if any.

  // Run command loop.
  lsh_loop();

  // Perform any shutdown/cleanup.

  return EXIT_SUCCESS;
}

 // main shell loop, that will read, parse, and execute the shell lines
void lsh_loop(){
    char *line;
    char **args;
    int status;

    do{
        printf("> ");
        line = lsh_readline();
        args = lsh_split_line(line);
        status = lsh_execute(args);

        free(line);
        free(args);
    } while (status);

}

//read the lines from the shell
char *lsh_read_line(void){
    char *line = NULL;
    ssize_t bufsize = 0;//getline will allocate the buffer size automatically
    //read the line from standard input
    if (getline(&line, &bufsize, stdin) == -1){
        if (feof(stdin)){
            exit(EXIT_SUCCESS);//success if reached end of file
        } else {
            perror("readline");
            exit(EXIT_FAILURE);//otherwise fail
        }
    }

    return line;

}

//split and parse the line into tokens 
char **lsh_split_line(char *line){
    int bufsize = LSH_TOK_BUFSIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;

    //checks if memory is allocated properly
    if (!tokens){
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
    }
    //take the first argument from line
    token = strtok(line, LSH_TOK_DELIM);

    //while there are still arguments on the line, place them into token
    while (token != NULL){
        //store each token into tokens
        tokens[position] = token;
        position++;

        if (position >= bufsize){
            // if tokens runs out of memory, add more to it
            bufsize += LSH_TOK_BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char));
            //check again if memory allocation worked
            if (!tokens) {
                fprintf(stderr, "lsh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, LSH_TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}

int lsh_launch(char **args){
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid = 0){
        //child process
        if (execvp(args[0], args) == 1){
            perror("lsh: argument fail");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0){
        perror("lsh: fork fail");
    } else {
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}

