#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>
#include<sys/wait.h>

struct message{
    long mtype;
    char mtext[8192];
};

int main()
{
    int msqid = msgget(IPC_PRIVATE,IPC_CREAT|0600);
    if(msqid==-1){
        puts("msgget: ERROR");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if(pid==0){
        struct message Message;
        Message.mtype = 23;
        memset(&(Message.mtext),0,8192*sizeof(char));
        (void)strncpy(Message.mtext,"Hallo Parrent's",strlen("Hallo Parrent's"));

        if(msgsnd(msqid,&Message,sizeof(long)+strlen(Message.mtext) * sizeof(char)+1,0) == -1){
            puts("msgsnd: ERROR");
            exit(EXIT_FAILURE);
        }
    }else{
        (void)waitpid(pid,NULL,0);
        struct message Message;
        if(msgrcv(msqid,&Message,8192,0,0)==-1){
            puts("msgrcv: ERROR");
            exit(EXIT_FAILURE);
        }
        printf("pesan: %s\n",Message.mtext);

        if(msgctl(msqid,IPC_RMID,NULL)==-1){
            puts("msgctl: ERROR");
            exit(EXIT_FAILURE);
        }
    }

    return EXIT_FAILURE;
}


