#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>

#define PORT 8080

int main()
{
    char msg_server[0x500] = "Panggilan server";

    int sock_server = socket(AF_INET,SOCK_STREAM,0);
    if(sock_server==-1){
        perror("sock_server socket");
        return EXIT_FAILURE;
    }

    struct sockaddr_in server = {
        .sin_addr.s_addr = INADDR_ANY,
        .sin_port = htons(PORT),
        .sin_family = AF_INET
    };

    if(bind(sock_server,(struct sockaddr*)&server,sizeof(server))==-1){
        perror("bind server: ");
        return EXIT_FAILURE;
    }

    if(listen(sock_server,5)==-1){
        perror("sock_server listen:");
        return EXIT_FAILURE;
    }

    int sock_client;
    if((sock_client = accept(sock_server,NULL,NULL))==-1){
        perror("accept sock_client");
        return EXIT_FAILURE;
    }

    if(send(sock_client,msg_server,sizeof(msg_server),0)==-1){
        perror("send sock_client:");
        return EXIT_FAILURE;
    }

    close(sock_server);

    return EXIT_SUCCESS;
}