#include<asm-generic/socket.h>
#include<netinet/in.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<poll.h>
#include<unistd.h>
#include<string.h>

#define PORT 8080
int main()
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    if((server_fd = socket(AF_INET,SOCK_STREAM,0)) < 0){
        perror("socket: ");
        exit(EXIT_FAILURE);
    }

    if(setsockopt(server_fd,SOL_SOCKET,SO_REUSEADDR|SO_REUSEPORT,&opt,sizeof(opt))<0){
        perror("setsockopt: ");
        return EXIT_FAILURE;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if(bind(server_fd,(struct sockaddr*)&address,sizeof(address))<0){
        perror("bind: ");
        return EXIT_FAILURE;
    }

    if(listen(server_fd,3)<0){
        perror("listen: ");
        return EXIT_FAILURE;
    }

    puts("menunggu koneksi tersambung");

    struct pollfd fds[2];
    int timeout_ms = -1;
    fds[0].fd = 0;
    fds[0].events = POLLIN;

    fds[1].fd = server_fd;
    fds[1].events = POLLIN;

    while(1){
        int result = poll(fds,2,timeout_ms);
        if(result==-1){
            perror("poll: ");
            return EXIT_FAILURE;
        }

        if(fds[0].revents & POLLIN){
            char buff[1000];
            ssize_t bytesRead = read(0,buff,sizeof(buff));
            if(bytesRead==-1){
                perror("read: ");
                return EXIT_FAILURE;
            }
            if(strncmp(buff,"exit",strlen("exit"))==0){
                close(new_socket);
                goto keluar;
            }
            printf("inputan dari stdin: %.*s\n" ,(int)bytesRead,buff);
        }

        if(fds[1].revents & POLLIN){
            if((new_socket = accept(server_fd,(struct sockaddr*)&address,(socklen_t*)&addrlen))<0){
                perror("accept: ");
                return EXIT_FAILURE;
            }
            char buffer[1000];
            int byteread = read(new_socket,buffer,sizeof(buffer));
            if(byteread==-1){
                perror("read sock: ");
                return EXIT_FAILURE;
            }
            if(strncmp(buffer,"exit",strlen("exit"))==0){
                close(new_socket);
                goto keluar;
            }

            printf("inputan dari socket: %.*s\n" ,(int)byteread,buffer);
            close(new_socket);

        }
    }
keluar:
    printf("keluar\n");
    return EXIT_SUCCESS;
}