#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
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

int open_netlink_socket()
{
    int sock_fd = socket(AF_NETLINK, SOCK_RAW, NETLINK_NETFILTER);
    if (sock_fd < 0)
        die("socket");

    struct sockaddr_nl src_addr;
    memset(&src_addr, 0, sizeof(src_addr));
    src_addr.nl_family = AF_NETLINK;
    src_addr.nl_pid = getpid();
    src_addr.nl_groups = 0;

    if (bind(sock_fd, (struct sockaddr *)&src_addr, sizeof(src_addr)) < 0)
        die("bind");

    return sock_fd;
}

void send_netlink_message(int sock_fd, struct nlmsghdr *nlh)
{
    struct sockaddr_nl dest_addr;
    struct iovec iov;
    struct msghdr msg;

    memset(&dest_addr, 0, sizeof(dest_addr));
    dest_addr.nl_family = AF_NETLINK;
    dest_addr.nl_pid = 0;
    dest_addr.nl_groups = 0;

    iov.iov_base = (void *)nlh;
    iov.iov_len = nlh->nlmsg_len;
    msg.msg_name = (void *)&dest_addr;
    msg.msg_namelen = sizeof(dest_addr);
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;

    if (sendmsg(sock_fd, &msg, 0) < 0)
        die("sendmsg");
}

void add_table(int sock_fd, const char *table_name)
{
    struct {
        struct nlmsghdr nlh;
        struct nfgenmsg nfg;
        char buf[256];
    } req;

    memset(&req, 0, sizeof(req));
    req.nlh.nlmsg_len = NLMSG_LENGTH(sizeof(req.nfg));
    req.nlh.nlmsg_type = (NFNL_SUBSYS_NFTABLES << 8) | NFT_MSG_NEWTABLE;
    req.nlh.nlmsg_flags = NLM_F_REQUEST | NLM_F_CREATE | NLM_F_ACK;
    req.nlh.nlmsg_seq = 0;
    req.nlh.nlmsg_pid = getpid();

    req.nfg.nfgen_family = AF_INET;
    req.nfg.version = NFNETLINK_V0;
    req.nfg.res_id = htons(0);

    struct nlattr *nla = (struct nlattr *)((char *)&req + NLMSG_ALIGN(req.nlh.nlmsg_len));
    nla->nla_type = NFTA_TABLE_NAME;
    nla->nla_len = NLA_HDRLEN + strlen(table_name) + 1;
    strcpy((char *)NFA_DATA(nla), table_name);
    req.nlh.nlmsg_len = NLMSG_ALIGN(req.nlh.nlmsg_len) + nla->nla_len;

    send_netlink_message(sock_fd, &req.nlh);
}

void add_chain(int sock_fd, const char *table_name, const char *chain_name)
{
    struct {
        struct nlmsghdr nlh;
        struct nfgenmsg nfg;
        char buf[256];
    } req;

    memset(&req, 0, sizeof(req));
    req.nlh.nlmsg_len = NLMSG_LENGTH(sizeof(req.nfg));
    req.nlh.nlmsg_type = (NFNL_SUBSYS_NFTABLES << 8) | NFT_MSG_NEWCHAIN;
    req.nlh.nlmsg_flags = NLM_F_REQUEST | NLM_F_CREATE | NLM_F_ACK;
    req.nlh.nlmsg_seq = 0;
    req.nlh.nlmsg_pid = getpid();

    req.nfg.nfgen_family = AF_INET;
    req.nfg.version = NFNETLINK_V0;
    req.nfg.res_id = htons(0);

    struct nlattr *nla = (struct nlattr *)((char *)&req + NLMSG_ALIGN(req.nlh.nlmsg_len));
    nla->nla_type = NFTA_CHAIN_TABLE;
    nla->nla_len = NLA_HDRLEN + strlen(table_name) + 1;
    strcpy((char *)NFA_DATA(nla), table_name);
    req.nlh.nlmsg_len = NLMSG_ALIGN(req.nlh.nlmsg_len) + nla->nla_len;

    nla = (struct nlattr *)((char *)&req + NLMSG_ALIGN(req.nlh.nlmsg_len));
    nla->nla_type = NFTA_CHAIN_NAME;
    nla->nla_len = NLA_HDRLEN + strlen(chain_name) + 1;
    strcpy((char *)NFA_DATA(nla), chain_name);
    req.nlh.nlmsg_len = NLMSG_ALIGN(req.nlh.nlmsg_len) + nla->nla_len;

    send_netlink_message(sock_fd, &req.nlh);
}

void add_rule(int sock_fd, const char *table_name, const char *chain_name, const char *expr)
{
    struct {
        struct nlmsghdr nlh;
        struct nfgenmsg nfg;
        char buf[256];
    } req;

    memset(&req, 0, sizeof(req));
    req.nlh.nlmsg_len = NLMSG_LENGTH(sizeof(req.nfg));
    req.nlh.nlmsg_type = (NFNL_SUBSYS_NFTABLES << 8) | NFT_MSG_NEWRULE;
    req.nlh.nlmsg_flags = NLM_F_REQUEST | NLM_F_CREATE | NLM_F_ACK;
    req.nlh.nlmsg_seq = 0;
    req.nlh.nlmsg_pid = getpid();

    req.nfg.nfgen_family = AF_INET;
    req.nfg.version = NFNETLINK_V0;
    req.nfg.res_id = htons(0);

    struct nlattr *nla = (struct nlattr *)((char *)&req + NLMSG_ALIGN(req.nlh.nlmsg_len));
    nla->nla_type = NFTA_RULE_TABLE;
    nla->nla_len = NLA_HDRLEN + strlen(table_name) + 1;
    strcpy((char *)NFA_DATA(nla), table_name);
    req.nlh.nlmsg_len = NLMSG_ALIGN(req.nlh.nlmsg_len) + nla->nla_len;

    nla = (struct nlattr *)((char *)&req + NLMSG_ALIGN(req.nlh.nlmsg_len));
    nla->nla_type = NFTA_RULE_CHAIN;
    nla->nla_len = NLA_HDRLEN + strlen(chain_name) + 1;
    strcpy((char *)NFA_DATA(nla), chain_name);
    req.nlh.nlmsg_len = NLMSG_ALIGN(req.nlh.nlmsg_len) + nla->nla_len;

    nla = (struct nlattr *)((char *)&req + NLMSG_ALIGN(req.nlh.nlmsg_len));
    nla->nla_type = NFTA_RULE_EXPRESSIONS;
    nla->nla_len = NLA_HDRLEN + strlen(expr) + 1;
    strcpy((char *)NFA_DATA(nla), expr);
    req.nlh.nlmsg_len = NLMSG_ALIGN(req.nlh.nlmsg_len) + nla->nla_len;

    send_netlink_message(sock_fd, &req.nlh);
}

int main(void)
{
    int sock_fd = open_netlink_socket();

    // Add a table
    add_table(sock_fd, "my_table");

    // Add a chain
    add_chain(sock_fd, "my_table", "my_chain");

    // Add a rule
    add_rule(sock_fd, "my_table", "my_chain", "match payload offset 0x0 length 0x4");

    close(sock_fd);
    return 0;
}
