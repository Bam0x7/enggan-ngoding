#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <syscall.h>
#include <sys/msg.h>

int main()
{
    char buff[0x2000];
    memset(buff,0,sizeof(buff));
    typedef struct{
        long mtype;
        char mtext[1];

    }msg;

    msg *message = (msg*)buff;
    msg *msg2 = (msg*)buff;
    msg *msg3 = (msg*)buff;

    int msqid = msgget(IPC_PRIVATE,0666|IPC_CREAT);

    for(int i=0; i < 2; i++){
        if(msqid==-1){
            perror("msgget:");
            return EXIT_FAILURE;
        }
    }

    message->mtype = 1;
    memset(message->mtext,'A',0x1010);

    if(msgsnd(msqid,message,0x200,0)==-1){
        perror(msgsnd);
        return EXIT_FAILURE;
    }
    msg2->mtype = 2;
    memset(msg2->mtext,'B',0x1010);
    if(msgsnd(msqid,msg2,0x1010 - 0x30,0)==-1){
        perror("msgsnd");
        return EXIT_FAILURE;
    }

    if(msgrcv(msqid,msg3,0x1000,0,IPC_NOWAIT|MSG_COPY|MSG_NOERROR)==-1){
        perror("msgrcv:");

        return EXIT_FAILURE;
    }

    printf("%s\n" ,msg3->mtext);
    printf("%d\n" ,msg3->mtype);

    return EXIT_SUCCESS;
}