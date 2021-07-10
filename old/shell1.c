#include <stdio.h>
#include <stdlib.h>
#include <fileio.h>
#include <string.h>
#define clear printf("\e[H\e[J")
#define CMD_SIZE 100

void prompt(char *out) {
    printf("> ");
    scanf("%s", out);
}

int main(int argc, char const **argv) {
    char *cmd=malloc(sizeof(char)*CMD_SIZE);
    int status=0;
    prompt(cmd);
    while(1) {
        status=0;
        if(!strcmp(cmd, "ls")) {
            ls(".");
            status=1;
        } else if(!strcmp(cmd, "exit")) {
            break;
        } else if(!strcmp(cmd, "clear")) {
            clear;
            status=1;
        } else {
            fprintf(stderr, "ish error: unknown command \"%s\"!\n", cmd);
            status=1;
        }
        if(status==1) {
            prompt(cmd);
        }
    }
    
    free(cmd);
    return 0;
}

