#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>

char **get_input(char *input) {
    //will hold the command
    char **command=malloc(sizeof(char *)*8);
    //the separator for strtok
    char *separator=" ";
    //will hold the parsed output from strtok
    char *parsed;
    int index=0;

    //strotk returns the first word in 'input' before the space
    parsed=strtok(input, separator);
    //while that word isn't NULL
    while(parsed!=NULL) {
        command[index]=parsed; //copy it to command[index]
        index++; //increment index
        parsed=strtok(NULL, separator); //get the next word from strtok
    }

    command[index]=NULL;
    return command;
}

int cd(char **args) {
    if(!strcmp(args[1], "~")) {
        strcpy(args[1], "/home");
    }
    if(!args[1]) {
        fprintf(stderr, "ish: cd: expected argument!\n");
    } else {
        if(chdir(args[1])!=0) {
            perror("ish");
        }
    }
    return 1;
}

void prompt_refresh(char *prompt) {
    char pwd[1024], hostname[1024], *user=getenv("USER");
    getcwd(pwd, sizeof(pwd));
    gethostname(hostname, sizeof(hostname));
    sprintf(prompt, "\e[1;32m%s@%s\e[0m:\e[1;34m%s $\e[0m ", user, hostname, pwd);
}

int main(int argc, char **argv) {
    char **command;
    char *input;
    pid_t child_pid; //pid_t==int
    int stat_loc, exit=0;
    char prompt[2048];
    prompt_refresh(prompt);

    //while exit isn't 1, run the code inside the loop
    while(exit!=1) {
        input=readline(prompt); //display the prompt and get a line from the user. the line is saved in 'input'
        command=get_input(input); //parse the input and save save it in 'command'
        add_history(input);

        //handel builtin shell commands
        if(!strcmp(command[0], "cd")) {
            cd(command);
            prompt_refresh(prompt);
            continue;
        } else if(!strcmp(command[0], "exit")) {
            printf("exit\n");
            exit=1;
            continue;
        } else if(!strcmp(command[0], "echo")||!strcmp(command[0], "printf")&&!strcmp(command[1], "$?")) {
            printf("%d\n", stat_loc);
            continue;
        }

        //fork the shell process
        child_pid=fork();
        if(child_pid==0) { //when the child process gets here, its 'child_pid' is 0 because it has no child
            if(execvp(command[0], command)==-1) { //run the command (execvp returns (-1) only if the process failed)
                perror("ish"); //error handling
                exit=1; //set exit to 1 for 'if' statement a t the end of the loop
            }
        } else if(child_pid<0) {
            perror("ish");
        } else {
            waitpid(child_pid, &stat_loc, WUNTRACED); //parent process waits until child has finished
        }

        //free input and command memory
        free(input);
        free(command);
        //if exit is 1 (set if the command failed to run), return from the child process and set exit to 0 again.
        if(exit==1) {
            return 0;
            exit=0;
        }
    }
    return 0;
}