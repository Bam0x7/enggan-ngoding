#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <linux/netfilter.h>
#include <linux/netfilter/nf_tables.h>
#include <linux/netfilter/nfnetlink.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>

#define NETLINK_NFLOG 5

void die(const char *s)
{
    perror(s);
    exit(EXIT_FAILURE);
}

int main(void)
{
    int sock_fd;
    struct sockaddr_nl src_addr, dest_addr;
    struct nlmsghdr *nlh = NULL;
    struct nfgenmsg *nfg = NULL;
    struct iovec iov;
    struct msghdr msg;
    char buffer[4096];

    // Create socket
    sock_fd = socket(AF_NETLINK, SOCK_RAW, NETLINK_ROUTE);
    if (sock_fd < 0)
        die("socket");

    // Zero out the source address structure
    memset(&src_addr, 0, sizeof(src_addr));
    src_addr.nl_family = AF_NETLINK;
    src_addr.nl_pid = getpid(); // Set the process ID
    src_addr.nl_groups = 0; // No multicast groups

    // Bind the socket
    if (bind(sock_fd, (struct sockaddr *)&src_addr, sizeof(src_addr)) < 0)
        die("bind");

    // Zero out the destination address structure
    memset(&dest_addr, 0, sizeof(dest_addr));
    dest_addr.nl_family = AF_NETLINK;
    dest_addr.nl_pid = 0; // For Linux kernel
    dest_addr.nl_groups = 0; // No multicast groups

    // Allocate memory for the Netlink message header
    nlh = (struct nlmsghdr *)malloc(NLMSG_SPACE(sizeof(struct nfgenmsg)));
    if (!nlh)
        die("malloc");

    // Zero out the Netlink message header
    memset(nlh, 0, NLMSG_SPACE(sizeof(struct nfgenmsg)));
    nlh->nlmsg_len = NLMSG_SPACE(sizeof(struct nfgenmsg));
    nlh->nlmsg_pid = getpid();
    nlh->nlmsg_flags = 0;

    // Allocate memory for the nfgenmsg structure
    nfg = (struct nfgenmsg *)NLMSG_DATA(nlh);
    nfg->nfgen_family = AF_UNSPEC;
    nfg->version = NFNETLINK_V0;

    // Set up the I/O vector
    iov.iov_base = (void *)nlh;
    iov.iov_len = nlh->nlmsg_len;
    msg.msg_name = (void *)&dest_addr;
    msg.msg_namelen = sizeof(dest_addr);
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;

    // Send the message
    if (sendmsg(sock_fd, &msg, 0) < 0)
        die("sendmsg");

    // Receive the response
    memset(buffer, 0, sizeof(buffer));
    iov.iov_base = buffer;
    iov.iov_len = sizeof(buffer);
    msg.msg_name = (void *)&src_addr;
    msg.msg_namelen = sizeof(src_addr);
    if (recvmsg(sock_fd, &msg, 0) < 0)
        die("recvmsg");

    // Process the response
    printf("Received message: %s\n", buffer);

    // Clean up
    close(sock_fd);
    free(nlh);

    return 0;
}
