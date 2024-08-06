#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdint.h>
#include<string.h>
#include<netinet/in.h>
#include<linux/netfilter.h>
#include<linux/netfilter/nfnetlink.h>
#include<linux/netfilter/nf_tables.h>
#include<linux/netlink.h>
#include<linux/rtnetlink.h>
#include<libmnl/libmnl.h>
#include<libnftnl/chain.h>
#include<libnftnl/batch.h>
#include<libnftnl/common.h>
#include<libnftnl/rule.h>

struct nftnl_chain *table_add_parse(char *name)
{
    struct nftnl_chain *t;
    uint16_t family;

    if(strcmp(name,"ip")==0){
        family = NFPROTO_IPV4;
    }else if(strcmp(name,"ip6")==0){
        family = NFPROTO_IPV6;
    }else if(strcmp(name,"bridge")==0){
        family = NFPROTO_BRIDGE;
    }else if(strcmp(name,"arp")==0){
        family = NFPROTO_ARP;
    }else{
        fprintf(stderr,"unknown fmaily: ip4, ip6, bridge, arp\n");
        return NULL;
    }

    t = nftnl_chain_alloc();
    if(t==NULL){
        perror("OOM");
        return NULL;
    }

    nftnl_chain_set_u32(t,NFTNL_CHAIN_FAMILY,family);
    nftnl_chain_set_str(t,NFTNL_CHAIN_TABLE,name);

    return t;
}

int main(int argc, char const *argv[])
{
    struct mnl_socket *mnl;
    struct nlmsghdr *nlh;
    char buff[MNL_SOCKET_BUFFER_SIZE];
    struct nftnl_chain *nft;
    struct mnl_nlmsg_batch *mnl_batch;
    uint32_t portid, seq, table_seq, family;
    int ret, batching;

    nft = table_add_parse("ip6");
    if(nft==NULL){
        perror("table_add_parse");
        return EXIT_FAILURE;
    }


    seq = time(NULL);
    mnl_batch = mnl_nlmsg_batch_start(buff,sizeof(buff));
    if(mnl_batch){
        nftnl_batch_begin(buff,seq++);
        mnl_nlmsg_batch_next(mnl_batch);
    }
    
    table_seq = seq;
    family = nftnl_chain_get_u32(nft,NFTNL_CHAIN_FAMILY);
    nlh = nftnl_chain_nlmsg_build_hdr(mnl_nlmsg_batch_current(mnl_batch),
                                      NFT_MSG_NEWTABLE,family,
                                      NLM_F_ACK,seq++);

    nftnl_chain_nlmsg_build_payload(nlh,nft);
    nftnl_chain_free(nft);
    mnl_nlmsg_batch_next(mnl_batch);

    if(mnl_batch){
        nftnl_batch_end(buff,seq++);
        mnl_nlmsg_batch_next(mnl_batch);
    }

    mnl = mnl_socket_open(NETLINK_NETFILTER);
    if(mnl==NULL){
        perror("mnl_socket_open");
        return EXIT_FAILURE;
    }

    if(mnl_socket_bind(mnl,0,MNL_SOCKET_AUTOPID)==-1){
        perror("mnl_socket_bind");
        return EXIT_FAILURE;
    }

    portid = mnl_socket_get_portid(mnl);
    if(mnl_socket_sendto(mnl,mnl_nlmsg_batch_head(mnl_batch),mnl_nlmsg_batch_size(mnl_batch))==-1){
        perror("mnl_socket_sendto");
        return EXIT_FAILURE;
    }

    mnl_nlmsg_batch_stop(mnl_batch);
    ret = mnl_socket_recvfrom(mnl,buff,sizeof(buff));
    while(ret>0){
        ret = mnl_cb_run(buff,ret,table_seq,portid,NULL,NULL);
        if(ret<=0){
            break;
        }
        ret = mnl_socket_recvfrom(mnl,buff,sizeof(buff));
    }
    if(ret==-1){
        perror("mnl_socket_recvfrom_2");
        return EXIT_FAILURE;
    }

    mnl_socket_close(mnl);
    return 0;
}

