#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<unistd.h>

#define PORT 8080
int main()
{
    int sock_client = socket(AF_INET,SOCK_STREAM,0);
    if(sock_client==-1){
        perror("sock_client socket");
        return EXIT_FAILURE;
    }

    struct sockaddr_in server;

    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);

    if(connect(sock_client,(struct sockaddr*)&server,sizeof(server)==-1)){
        perror("sock_client connect");
        return EXIT_FAILURE;
    }

    char msg_response[0x500];
    recv(sock_client,&msg_response,sizeof(msg_response),0);
    printf("server: %s\n" ,msg_response);

    close(sock_client);

    return EXIT_SUCCESS;
}