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

void *handle_client(void *arg)
{
    int client_sock = *(int*)arg;
    char buff[BUF_MAX];
    memset(buff,0,sizeof(buff));

    while(1){
        int val = read(client_sock,buff,sizeof(buff));
        if(val==-1){
            perror("read");
            close(client_sock);
            goto _disconnected;
        }

        if(strncmp(buff,"exit",4)==0){
            close(client_sock);
            goto _exit_socket;
        }else{
            printf("client: %s\n" ,buff);
        }

        memset(buff,0,sizeof(buff));
        printf(">> ");
        scanf("%s" ,buff);

        if(strncmp(buff,"exit",4)==0){
            printf("anda keluar");
            close(client_sock);
            goto _exit_socket;
        }else{
            send(client_sock,buff,sizeof(buff),0);
        }
    }

_disconnected:
    exit(EXIT_FAILURE);    

_exit_socket:
    printf("anda keluar");
    exit(EXIT_SUCCESS);    
}


int main()
{
    int sock_fd,client;

    sock_fd = socket(AF_INET,SOCK_STREAM,0);
    if(sock_fd==0){
        perror("socket error:");
        close(sock_fd);
        return EXIT_FAILURE;
    }

    struct sockaddr_in server = {
        .sin_addr.s_addr = INADDR_ANY,
        .sin_family = AF_INET,
        .sin_port = htons(PORT)
    };

    if(bind(sock_fd,(struct sockaddr*)&server,sizeof(server))==-1){
        perror("socket bind");
        close(sock_fd);
        return EXIT_FAILURE;
    }

    if(listen(sock_fd,10)==-1){
        perror("socket listen");
        close(sock_fd);
        return EXIT_FAILURE;
    }
    printf("server listened in port: %d\n" ,PORT);
    sleep(1);

    while(1){

        if((client = accept(sock_fd,(struct sockaddr*)&server,(socklen_t*)&server))==-1){
            perror("client accept:");
            close(sock_fd);
            goto err_sock;
        }

        puts("koneksi baru diterima");

        pthread_t th;

        if(pthread_create(&th,NULL,handle_client,&client)==-1){
            perror("pthread_create:");
            close(sock_fd);
            goto err_sock;
        }

        pthread_detach(th);
    }

err_sock:
    exit(EXIT_FAILURE);


    return EXIT_SUCCESS;
}