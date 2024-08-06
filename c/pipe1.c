#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sched.h>
#include<sys/stat.h>
#include<sys/types.h>

int main()
{
    int fd[2];
    char buff[20];

    if(pipe(fd)==-1){
        perror("pipe");
        return EXIT_FAILURE;
    }

    pid_t pid = fork();
    if(pid==-1){
        perror("fork");
        return EXIT_FAILURE;
    }

    if(pid>0){
        close(fd[0]);
        write(fd[1],"hello, child",13);
        close(fd[1]);
    }else{
        close(fd[1]);
        read(fd[0],buff,sizeof(buff));
        close(fd[0]);
        printf("buffer di terima: %s\n" ,buff);
    }

    return EXIT_SUCCESS;
}