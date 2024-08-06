#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<net/if.h>
#include<linux/netlink.h>
#include<linux/rtnetlink.h>
#include<linux/netfilter/nfnetlink.h>
#include<libmnl/libmnl.h>

char buffer[4096];
//inisialisasi socket netlink

int createSOckNetlink()
{
    struct sockaddr_nl addr;
    int sock;

    sock = socket(AF_NETLINK,SOCK_RAW,NETLINK_ROUTE);
    if(sock==-1){
        perror("socket");
        return EXIT_FAILURE;
    }

    memset(&addr,0,sizeof(addr));

    addr.nl_family = AF_NETLINK; 
    if(bind(sock,(struct sockaddr*)&addr,sizeof(addr))==-1){
        perror("bind");
        return EXIT_FAILURE;
    }

    return sock;
}

void sendLInkMsg(int sock, struct nlmsghdr *nlh)
{
    if(send(sock,nlh,nlh->nlmsg_len,0)==-1){
        perror("send");
        exit(EXIT_FAILURE);
    }
    
} 

void rcvLinkMsg(int sock)
{
    struct nlmsghdr *nlh;

    ssize_t recvlen = recv(sock,buffer,sizeof(buffer),0);
    if(recvlen==-1){
        perror("recv");
        exit(EXIT_FAILURE);
    }

    for (nlh = (struct nlmsghdr *)buffer; NLMSG_OK(nlh, (size_t)recvlen); nlh = NLMSG_NEXT(nlh, recvlen)){
        if (nlh->nlmsg_type == NLMSG_DONE) {
            exit(EXIT_FAILURE);
        }

        // Implementasi pemrosesan pesan Netlink di sini
        // ...
    }
}

int main(int argc, char const *argv[])
{
    int sock = createSOckNetlink();

    struct nlmsghdr *nlh;
    struct mnl_socket *nl;

    nl = mnl_socket_open(NETLINK_ROUTE);
    if(nl==NULL){
        perror("mnl_socket_open");
        return EXIT_FAILURE;
    }

    nlh = mnl_nlmsg_put_header(buffer);
    nlh->nlmsg_type = RTM_GETLINK;
    nlh->nlmsg_flags = NLM_F_REQUEST | NLM_F_DUMP;
    nlh->nlmsg_seq = 1;
    nlh->nlmsg_pid = getpid();

    //mengirim pesan netlink
    if(mnl_socket_sendto(nl,nlh,nlh->nlmsg_len)==-1){
        perror("mnl_socket_sendto");
        return EXIT_FAILURE;
    }

    //menerima netlink
    if(mnl_socket_recvfrom(nl,buffer,sizeof(buffer))==-1){
        perror("mnl_socket_recvfrom");
        return EXIT_FAILURE;
    }

    close(sock);
    mnl_socket_close(nl);

    return 0;
}
