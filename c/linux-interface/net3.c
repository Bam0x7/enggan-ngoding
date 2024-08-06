#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>
#include <libmnl/libmnl.h>

#include <stdio.h>
#include <stdlib.h>
#include <libmnl/libmnl.h>

int main() {
    struct mnl_socket *nl;
    char buf[MNL_SOCKET_BUFFER_SIZE];
    struct nlmsghdr *nlh;
    struct rtattr attr;
    int ret;

    // Inisialisasi pustaka libmnl
    nl = mnl_socket_open(NETLINK_ROUTE);
    if (nl == NULL) {
        perror("mnl_socket_open");
        exit(EXIT_FAILURE);
    }

    // Membuat pesan Netlink
    nlh = mnl_nlmsg_put_header(buf);
    nlh->nlmsg_type = RTM_GETLINK;
    nlh->nlmsg_flags = NLM_F_REQUEST | NLM_F_DUMP;
    nlh->nlmsg_seq = 1;
    nlh->nlmsg_pid = getpid();

    // Mengirim pesan Netlink
    if (mnl_socket_sendto(nl, buf, nlh->nlmsg_len) < 0) {
        perror("mnl_socket_sendto");
        mnl_socket_close(nl);
        exit(EXIT_FAILURE);
    }

    // Menerima dan memproses pesan Netlink
    ret = mnl_socket_recvfrom(nl, buf, sizeof(buf));
    if (ret == -1) {
        perror("mnl_socket_recvfrom");
        mnl_socket_close(nl);
        exit(EXIT_FAILURE);
    }

    // Implementasi pemrosesan pesan Netlink di sini
    // ...

    // Menutup socket dan pustaka libmnl
    mnl_socket_close(nl);

    return 0;
}
