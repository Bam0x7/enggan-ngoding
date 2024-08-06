#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/msg.h>
#include<sys/ipc.h>
#include<sys/wait.h>
#include<sys/types.h>

struct message{
    long mtype;
    char mtext[1024];
};
int main()
{
    int qid = msgget(IPC_PRIVATE, IPC_CREAT|0600);
    if(qid==-1){
        puts("msgget error");
        exit(EXIT_FAILURE);
    }    

    char pesan[1024] = "Hai, ini proses anak";
    pid_t pid = fork();
    if(pid==-1){
        puts("fork error");
        exit(EXIT_FAILURE);
    }else if(pid==0){
        struct message Message;
        Message.mtype = 1;
        memset(&(Message.mtext),0,sizeof(char)*1024);
        strncpy(Message.mtext,pesan,strlen(pesan));

        if(msgsnd(qid,&Message,sizeof(long)+strlen(Message.mtext)*sizeof(char),0)==-1){
            puts("msgsnd error");
            exit(EXIT_FAILURE);
        }
        
    }else{
        struct message Message;
        waitpid(pid,NULL,0);
        if(msgrcv(qid,&Message,1024,0,0)==-1){
            puts("msgrcv error");
            exit(EXIT_FAILURE);
        }
        printf("pesan: %s\n" ,Message.mtext);

        if(msgctl(qid,IPC_RMID,NULL)==-1){
            puts("msgctl error");
            exit(EXIT_FAILURE);
        }
    }

    return EXIT_SUCCESS;
}