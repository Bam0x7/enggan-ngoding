#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<net/if_packet.h>
#include<netinet/tcp.h>
#include<netinet/if_ether.h>
#include<libmnl/libmnl.h>
#include<libnftnl/common.h>
#include<libnftnl/chain.h>
#include<libnftnl/rule.h>
#include<linux/ethtool.h>
#include<linux/ethtool_netlink.h>
#include<linux/netlink.h>

int main(int argc, char const *argv[])
{
    int sock[2];

    //menggunakan socketpair
    if(socketpair(AF_UNIX,SOCK_STREAM,0,sock)==-1){
        perror("socketpair");
        return EXIT_FAILURE;
    }

    int reuse = 1;
    //menggunakan setsockopt
    if(setsockopt(sock[0],SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(reuse))&&
        setsockopt(sock[1],SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(reuse))==-1){
            perror("setsockopt");
            return EXIT_FAILURE;
    }
    pid_t pid = fork();
    if(pid==-1){
        perror("fork()");
        return EXIT_FAILURE;
    }else if(pid==0){
        close(sock[0]);
        char buff[256];
        //membaca pesan dari sock[1]
        ssize_t byteRead = read(sock[1],buff,sizeof(buff)-1);
        
        if(byteRead==-1){
            perror("read");
            return EXIT_FAILURE;
        }

        buff[byteRead] = '\0';
        printf("child menerima pesan %s\n" ,buff);

        close(sock[1]);
    }else{
        close(sock[1]);
        const char *msg = "pesan dari parent\n";

        //mengirim pesan pada socket
        ssize_t byteWrite = write(sock[0],msg,sizeof(msg)-1);
        if(byteWrite==-1){
            perror("write");
            return EXIT_FAILURE;
        }

        wait(NULL);
        close(sock[1]);
    }

    return 0;
}
