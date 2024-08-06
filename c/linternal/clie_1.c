#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<pthread.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/stat.h>

#define PORT 9001
#define BUF_MAX 0x25

void handle_conn(int sockfd)
{
    char buff[BUF_MAX];
    memset(buff,0,sizeof(buff));

    while(1){
        printf(">> ");
        scanf("%s" ,buff);

        if(strncmp(buff,"exit",4)==0){
            puts("anda keluar");
            goto _exit_conn;
        }else{
            send(sockfd,buff,sizeof(buff),0);
        }
        memset(buff,0,sizeof(buff));
        int val = read(sockfd,buff,sizeof(buff));
        if(val==-1){
            perror("gagal membaca pesan dari server");
            goto _exit_err;
        }

        if(strncmp(buff,"exit",4)==0){
            puts("anda keluar");
            goto _exit_conn;
        }else{
            printf("server: %s\n" ,buff);
        }
    }

_exit_conn:
    close(sockfd);
    exit(EXIT_SUCCESS);    


_exit_err:
    close(sockfd);
    exit(EXIT_FAILURE);
}



int main()
{
    int sockfd;
    
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd==-1){
        perror("sockfd socket");
        close(sockfd);
        return EXIT_FAILURE;
    }

    struct sockaddr_in server = {
        .sin_addr.s_addr = INADDR_ANY,
        .sin_port = htons(PORT),
        .sin_family = AF_INET
    };

    if(connect(sockfd,(struct sockaddr*)&server,sizeof(server))==-1){
        perror("sockfd connect");
        close(sockfd);
        return EXIT_FAILURE;
    }

    handle_conn(sockfd);    
}