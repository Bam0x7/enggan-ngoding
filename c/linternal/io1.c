#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/poll.h>
#include<linux/userfaultfd.h>

int main()
{
    struct pollfd fds[1];
    int timeout = 5000;

    fds[0].fd = 0;
    fds[0].events = POLLIN;

    printf("program waiting until five minutes\n");
    int result = poll(fds,1,timeout);
    if(result==-1){
        perror("poll");
        return EXIT_FAILURE;
    }else if(result==0){
        printf("input timeout\n");
    }else{
        if(fds[0].revents & POLLIN){
            printf("stdin reading....\n");
            char buff[0x1000];
            ssize_t byteRead = read(0,buff,sizeof(buff));
            if(byteRead==-1){
                perror("read");
                return EXIT_FAILURE;
            }
            printf("user input: %.*s\n" ,(int)byteRead,buff);
        }
    }


}