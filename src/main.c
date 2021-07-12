#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>

#define VER "0.2"
//pointer that will point to 'child_pid' in the main function for signal handler
pid_t *child;

char **get_input(char *input) {
    //will hold the command
    char **command=malloc(sizeof(char *)*8);
    //the separator for strtok
    char *separator=" ";
    //will hold the parsed output from strtok
    char *parsed;
    int index=0;

    //strtok returns the first word in 'input' before the space
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

void about() {
    printf("#### ish shell, version %s ####\n================================\n\n", VER);
    printf("Author: Itai Nelken\n");
    printf("Copyright (c) 2021 Itai Nelken\n");
    printf("License: MIT\n");
}

void help() {
    printf(" ish shell version %s \n======================\n\n", VER);
    printf("BUILT-IN COMMANDS:\n- cd [path]\n- about\n- help\n");
    printf("Type the path to a program or only its name\nif it is in your PATH to run it\n");
}

int cd(char **args) {
    //char temp[500], *path=malloc(sizeof(args[1])+1), *home=getenv("HOME");
    //int i;
    if(args[1]==NULL) {
        fprintf(stderr, "ish: cd: expected argument!\n");
    } else {
        /****************** pointer to first '~' from this loop
        for(i=0; i<sizeof(args[1]); i++) {
            strcpy(path, "");
            sprintf(path, "%c", args[1][i]);
            if(!strcmp(path, "~")) {
                break;
            }
        }
        ********************/
        //printf("path: %s\n", path);
        if(chdir(args[1])!=0) {
            perror("ish");
        } else {
            return 0;
        }
    }
    //free(path);
    return 1;
}

void prompt_refresh(char *prompt) {
    char pwd[1024], hostname[1024], *user=getenv("USER");
    getcwd(pwd, sizeof(pwd));
    gethostname(hostname, sizeof(hostname));
    // \001 = \[  \002 = \]
    // used to tell readline that the characters between the \001 and \002 aren't displayed
    // prevents the text overwriting the prompt issue.
    sprintf(prompt, "\001\e[1;32m\002%s@%s\001\e[0m\002:\001\e[1;34m\002%s $\001\e[0m\002 ", user, hostname, pwd);
}

#warning I know I shouldn'y use printf or any of the functions I'm calling in a signal handler... but it is the only way I have found to make it work the way I want...
void sigint_handler(pid_t sig) {
    char prompt[2048]="", *newline="\n";
    prompt_refresh(prompt);
    if(*child!=0) {
        kill(*child, SIGKILL);
        printf("\n");
    } else {
        //write(STDOUT_FILENO, newline, sizeof(newline));
        //write(STDOUT_FILENO, prompt, sizeof(prompt));
        printf("\n");
        printf("%s", prompt);
    }
}

int main(int argc, char **argv) {
    //handle ctrl+c (SIGINT)
    signal(SIGINT, sigint_handler);
    //handle command line arguments (when shell isn't running)
    if(argv[1]) {
        if(!strcmp(argv[1], "--help")) {
            help();
            return 0;
        } else if(!strcmp(argv[1], "--about")) {
            about();
            return 0;
        }
    }

    char **command;
    char *input;
    pid_t child_pid; //pid_t==int
    child=&child_pid;
    int stat_loc, exit=0;
    char prompt[2048];
    prompt_refresh(prompt);

    //while exit isn't 1, run the code inside the loop
    while(exit!=1) {
        input=readline(prompt); //display the prompt and get a line from the user. the line is saved in 'input'
        add_history(input);
        command=get_input(input); //parse the input and save save it in 'command'

        //shell features and stuff handling
        if(command[0]) {
            //handle built-in shell commands
            if(!strcmp(command[0], "cd")) {
                cd(command);
                prompt_refresh(prompt);
                continue;
            } else if(!strcmp(command[0], "exit")) {
                printf("exit\n");
                exit=1;
                continue;
            } else if(!strcmp(command[0], "about")) {
                about();
                continue;
            } else if(!strcmp(command[0], "help")) {
                help();
                continue;
            }
        }

        //fork the shell process
        child_pid=fork();
        if(child_pid==0) { //when the child process gets here, its 'child_pid' is 0 because it has no child
            if(execvp(command[0], command)==-1) { //run the command (execvp returns (-1) only if the process failed)
                perror("ish"); //error handling
                exit=1; //set exit to 1 for 'if' statement at the end of the loop
            }
        } else if(child_pid<0) {
            perror("ish");
        } else {
            waitpid(child_pid, &stat_loc, WUNTRACED); //parent process waits until child has finished
            child_pid=0;
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
