#include<stdio.h>
#include<stdlib.h>
#include<sys/ptrace.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<unistd.h>

int main(int argc, char *argv[])
{
    if(argc<2){
        fprintf(stderr,"gunakan %s <program/path>\n" ,argv[0]);
        exit(EXIT_FAILURE);
    }

    pid_t child_pid = fork();

    if(child_pid ==-1){
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if(child_pid==0){
        ptrace(PTRACE_TRACEME,0,NULL,NULL);
        execvp(argv[1],&argv[1]);
    }else{
        int status;
        waitpid(child_pid,&status,0);

        if(WIFEXITED(status)){
            printf("program anak selesai dengan kode keluar: %d\n" ,WEXITSTATUS(status));
            exit(EXIT_SUCCESS);
        }
        while(1){
            ptrace(PTRACE_SINGLESTEP,child_pid,NULL,NULL);
            waitpid(child_pid,&status,0);
            if(WIFEXITED(status)){
                printf("program anak selesai dengan kode: %d\n" ,WEXITSTATUS(status));
                break;
            }

            if(WIFSTOPPED(status)){
                if(WSTOPSIG(status)==SIGTRAP){
                    long eip = ptrace(PTRACE_PEEKUSER,child_pid,4*eip,NULL);
                    printf("nilai register eip: %lx\n" ,eip);
                }
            }
        }
    }

    return EXIT_SUCCESS;

}