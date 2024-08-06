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
    int sockfd = socket(AF_INET,SOCK_STREAM,0);

    if(sockfd==-1){
        perror("socket");
        return EXIT_FAILURE;
    }

    int sendBuff;
    socklen_t optlen = sizeof(sendBuff);

    if(getsockopt(sockfd,SOL_SOCKET,SO_SNDBUF,&sendBuff,&optlen)==-1){
        perror("getsockopt snd");
        return EXIT_FAILURE;
    }
    printf("ukuran buffer pengiriman (SO_SNDBUF): %d\n" ,sendBuff);

    int recvBuff;

    if(getsockopt(sockfd,SOL_SOCKET,SO_RCVBUF,&recvBuff,&optlen)==-1){
        perror("getsockopt recv");
        return EXIT_FAILURE;
    }

    printf("ukuran buffer penerima (SO_RCVBUF): %d\n" ,recvBuff);

    close(sockfd);
    return 0;
}
