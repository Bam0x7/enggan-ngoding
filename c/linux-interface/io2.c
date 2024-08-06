#define _GNU_SOURCE
#include<asm-generic/socket.h>
#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/poll.h>
#include<linux/userfaultfd.h>

#define PORT 8888

int main()
{
    int server,client;
    struct sockaddr_in sockfd;
    int opt = 1;
    int sockfd_len = sizeof(sockfd);

    if((server = socket(AF_INET,SOCK_STREAM,0))==-1){
        perror("socket");
        return EXIT_FAILURE;
    }

    if(setsockopt(server,SOL_SOCKET,SO_REUSEADDR|SO_REUSEPORT,&opt,sizeof(opt))==-1){
        perror("setsockopt");
        return EXIT_FAILURE;
    }

    sockfd.sin_family = AF_INET;
    sockfd.sin_addr.s_addr = INADDR_ANY;
    sockfd.sin_port = htons(PORT);

    if (bind(server,(struct sockaddr *)&sockfd,sizeof(sockfd))==-1){
        perror("bind");
        return EXIT_FAILURE;
    }

    if(listen(server,3)==-1){
        perror("listen");
        return EXIT_FAILURE;
    }

    printf("server listening on port %d\n" ,PORT);

    struct pollfd fds[2];
    
    fds[0].fd = 0;
    fds[0].events = POLLIN;

    fds[1].fd = server;
    fds[1].events = POLLIN;

    while(1){
        int result = poll(fds,2,5000);

        if(result==-1){
            perror("poll");
            return EXIT_FAILURE;
        }

        if(fds[0].revents & POLLIN){
            char buff[0x1000];
            ssize_t bytesRead = read(0,buff,sizeof(buff));

            if(bytesRead==-1){
                perror("read");
                return EXIT_FAILURE;
            }

            printf("data dari stdin %.*s\n" ,(int)bytesRead,buff);
        }

        if(fds[1].revents &POLLIN){
            if((client = accept(server,(struct sockaddr *)&sockfd,(socklen_t *)&sockfd))==-1){
                perror("accept");
                return EXIT_FAILURE;
            }

            char buff[0x1000];
            int byteRead = read(client,buff,sizeof(buff));

            if(byteRead==-1){
                perror("read");
                return EXIT_FAILURE;
            }

            printf("data dari socket %.*s\n" ,(int)byteRead,buff);
            close(server);
        }
    }

    return EXIT_SUCCESS;
}