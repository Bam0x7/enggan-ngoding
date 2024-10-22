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
#include <libnftnl/rule.h>
#include <libnftnl/expr.h>
#include <libnftnl/set.h>


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

struct nftnl_rule* build_rule(char* table_name, char* chain_name, uint32_t handle, uint16_t family) {
    struct nftnl_rule* r = nftnl_rule_alloc();
    nftnl_rule_set_u32(r, NFTNL_RULE_FAMILY, family);
    nftnl_rule_set_str(r, NFTNL_RULE_TABLE, table_name);
    nftnl_rule_set_str(r, NFTNL_RULE_CHAIN, chain_name);
    nftnl_rule_set_u64(r, NFTNL_RULE_HANDLE, handle);
    return r;
}

// Fungsi untuk membuat set
struct nftnl_set* build_set(char* set_name, char* table_name, uint16_t family, uint32_t key_len) {
    struct nftnl_set *s = nftnl_set_alloc();
    nftnl_set_set_str(s, NFTNL_SET_TABLE, table_name);
    nftnl_set_set_str(s, NFTNL_SET_NAME, set_name);
    nftnl_set_set_u32(s, NFTNL_SET_FAMILY, family);
    nftnl_set_set_u32(s, NFTNL_SET_KEY_LEN, key_len); // Panjang kunci
    nftnl_set_set_u32(s, NFTNL_SET_ID, 1);  // ID untuk set
    nftnl_set_set_u32(s, NFTNL_SET_FLAGS, 0);
    nftnl_set_set_u32(s, NFTNL_SET_DESC_SIZE, 0); // Ukuran deskripsi
    return s;
}

// Fungsi untuk menambahkan elemen ke set
struct nftnl_set_elem* build_set_elem(uint32_t key) {
    struct nftnl_set_elem *se = nftnl_set_elem_alloc();
    nftnl_set_elem_set(se, NFTNL_SET_ELEM_KEY, &key, sizeof(key)); // Menentukan elemen kunci
    return se;
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
	
    // Create table "test_table"
    struct nftnl_table * t = build_table("test_table", NFPROTO_IPV4);
    nlh = nftnl_nlmsg_build_hdr(mnl_nlmsg_batch_current(batch), NFT_MSG_NEWTABLE, family, NLM_F_CREATE | NLM_F_ACK, seq++);
    nftnl_table_nlmsg_build_payload(nlh, t);
    mnl_nlmsg_batch_next(batch);
	
	// Add basechain "chain1"
    struct unft_base_chain_param bp;
    bp.hook_num = NF_INET_LOCAL_OUT;
    bp.prio = 11;
    struct nftnl_chain * c = build_chain("test_table", "chain1", &bp, 11);
    nlh = nftnl_nlmsg_build_hdr(mnl_nlmsg_batch_current(batch), NFT_MSG_NEWCHAIN, family, NLM_F_CREATE | NLM_F_ACK, seq++);
    nftnl_chain_nlmsg_build_payload(nlh, c);
	mnl_nlmsg_batch_next(batch);

    // Create set "my_set"
    struct nftnl_set *s = build_set("my_set", "test_table", NFPROTO_IPV4, sizeof(uint32_t));
    nlh = nftnl_nlmsg_build_hdr(mnl_nlmsg_batch_current(batch), NFT_MSG_NEWSET, family, NLM_F_CREATE | NLM_F_ACK, seq++);
    nftnl_set_nlmsg_build_payload(nlh, s);
    mnl_nlmsg_batch_next(batch);

    // Add element to set
    struct nftnl_set_elem *se = build_set_elem(0xdeadbeef);  // Menambahkan elemen dengan kunci 0xdeadbeef
    nlh = nftnl_nlmsg_build_hdr(mnl_nlmsg_batch_current(batch), NFT_MSG_NEWSETELEM, family, NLM_F_CREATE | NLM_F_ACK, seq++);
    nftnl_set_elem_nlmsg_build_payload(nlh, se);
    mnl_nlmsg_batch_next(batch);

    // Create rule and add it to chain
    struct nftnl_rule *r = build_rule("test_table", "chain1", 1, family);

    // Create expression (set) and add it to rule
    struct nftnl_expr *e = nftnl_expr_alloc("lookup");
    nftnl_expr_set_str(e, NFTNL_EXPR_LOOKUP_SET, "set_table");
    nftnl_expr_set_u32(e, NFTNL_EXPR_LOOKUP_SREG, NFT_REG_1);
    nftnl_rule_add_expr(r, e);

    // Add the rule to the netlink message
    nlh = nftnl_nlmsg_build_hdr(mnl_nlmsg_batch_current(batch), NFT_MSG_NEWRULE, family, NLM_F_CREATE | NLM_F_ACK, seq++);
    nftnl_rule_nlmsg_build_payload(nlh, r);
    mnl_nlmsg_batch_next(batch);
    
    // End the batch
    nftnl_batch_end(mnl_nlmsg_batch_current(batch), seq++);
    mnl_nlmsg_batch_next(batch);
    
    // Send netlink message
    printf("[+] Sending netlink message...\n");
	ret = mnl_socket_sendto(nl, mnl_nlmsg_batch_head(batch), mnl_nlmsg_batch_size(batch));
    mnl_nlmsg_batch_stop(batch);
    if (ret < 0) {
        perror("mnl_socket_sendto");
        exit(EXIT_FAILURE);
    }

    // Clean up
    nftnl_table_free(t);
    nftnl_chain_free(c);
    nftnl_rule_free(r);
    nftnl_set_free(s);
    nftnl_set_elem_free(se);
    mnl_socket_close(nl);
    
    printf("[+] Done!\n");

    return 0;
}
