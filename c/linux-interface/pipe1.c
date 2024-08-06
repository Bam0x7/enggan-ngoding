#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define MAX_LINE 256

int main(void){

    int i, fileDesc[2];

    pid_t pid;
    char line[MAX_LINE];

    if(pipe(fileDesc)<0){
        printf("pipe error.\n");
        exit(EXIT_FAILURE);
    }

    if((pid=fork())<0){
        printf("fork error.\n");
        exit(EXIT_FAILURE);
    } 

    if(pid > 0){
        close(fileDesc[0]);
        char * szPtr = "You are likely to be eaten by a grue.\n";
        write(fileDesc[1], szPtr, strlen(szPtr));
    } else {
        //child process fork() == 0
        close(fileDesc[1]);
        read(fileDesc[0], line, MAX_LINE);
        printf("In child process: %s\n", line);
    
    }

    return 0;
}