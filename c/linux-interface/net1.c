#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/ioctl.h>
#include<net/if.h>
#include <linux/genetlink.h>
#include <linux/if_addr.h>
#include <linux/if_ether.h>
#include <linux/if_link.h>
#include <linux/if_tun.h>
#include <linux/in6.h>
#include <linux/ip.h>
#include <linux/neighbour.h>
#include <linux/net.h>
#include<linux/ethtool.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>
#include <linux/tcp.h>
#include <linux/veth.h>
#include <linux/pfkeyv2.h>
#include <linux/xfrm.h>
#include <linux/msg.h>
#include <sys/resource.h>



#define ETHTOOL_GLINK   0x0000000a  /* Get link status (ethtool_value) */

// Fungsi untuk mendapatkan informasi link status menggunakan ethtool
int getLinkStatus(const char *interface) {
    int sock, ret;
    struct ifreq ifr;
    struct ethtool_value edata;

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock == -1) {
        perror("socket");
        return -1;
    }

    memset(&ifr, 0, sizeof(struct ifreq));
    strncpy(ifr.ifr_name, interface, IFNAMSIZ - 1);

    edata.cmd = ETHTOOL_GLINK;
    ifr.ifr_data = (caddr_t)&edata;

    ret = ioctl(sock, SIOCSIFLINK, &ifr);
    close(sock);

    if (ret == -1) {
        perror("ioctl");
        return -1;
    }

    return edata.data;
}

// Fungsi untuk mendapatkan informasi antarmuka menggunakan Netlink
void getInterfaceInfo(const char *interface) {
    int sock, ret;
    struct sockaddr_nl addr;
    struct nlmsghdr *nlh;
    struct ifinfomsg *ifi;
    struct rtattr *rta;
    char buffer[4096];

    sock = socket(AF_NETLINK, SOCK_RAW, NETLINK_ROUTE);
    if (sock == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    memset(&addr, 0, sizeof(addr));
    addr.nl_family = AF_NETLINK;

    nlh = (struct nlmsghdr *)buffer;
    ifi = (struct ifinfomsg *)(buffer + NLMSG_HDRLEN);

    nlh->nlmsg_len = NLMSG_LENGTH(sizeof(struct ifinfomsg));
    nlh->nlmsg_type = RTM_GETLINK;
    nlh->nlmsg_flags = NLM_F_REQUEST | NLM_F_DUMP;
    nlh->nlmsg_seq = 1;
    nlh->nlmsg_pid = getpid();

    ifi->ifi_family = AF_UNSPEC;

    rta = (struct rtattr *)(buffer + NLMSG_ALIGN(nlh->nlmsg_len));
    rta->rta_len = RTA_LENGTH(0);

    if (sendto(sock, nlh, nlh->nlmsg_len, 0, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        perror("sendto");
        close(sock);
        exit(EXIT_FAILURE);
    }

    while (1) {
        ssize_t recvLen = recv(sock, buffer, sizeof(buffer), 0);
        if (recvLen == -1) {
            perror("recv");
            close(sock);
            exit(EXIT_FAILURE);
        }

        for (nlh = (struct nlmsghdr *)buffer; NLMSG_OK(nlh, (size_t)recvLen); nlh = NLMSG_NEXT(nlh, recvLen)) {
            if (nlh->nlmsg_type == NLMSG_DONE) {
                close(sock);
                return;
            }

            if (nlh->nlmsg_type == RTM_NEWLINK) {
                rta = IFLA_RTA(ifi);

                while (RTA_OK(rta, nlh->nlmsg_len)) {
                    if (rta->rta_type == IFLA_IFNAME) {
                        printf("Interface: %s\n", (char *)RTA_DATA(rta));
                    }

                    rta = RTA_NEXT(rta, nlh->nlmsg_len);
                }

                if (ifi->ifi_flags & IFF_UP) {
                    printf("Status: UP\n");
                } else {
                    printf("Status: DOWN\n");
                }

                int linkStatus = getLinkStatus(interface);
                if (linkStatus == 1) {
                    printf("Link Status: UP\n");
                } else if (linkStatus == 0) {
                    printf("Link Status: DOWN\n");
                } else {
                    printf("Link Status: Unknown\n");
                }

                printf("\n");
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Penggunaan: %s <interface>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *interface = argv[1];

    printf("Informasi antarmuka jaringan:\n");
    getInterfaceInfo(interface);

    return 0;
}
