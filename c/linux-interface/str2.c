#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdint.h>
#include<string.h>
struct ctx_t{
    uint64_t ctx_num;
    char ctx_char[1];
    struct ctx_t *next,*prev;
};

#define ERR(msg)    \
        do{          \
        printf("%s not allocated\n" ,msg);  \
        exit(EXIT_FAILURE);}while(0)

struct ctx_t *alloc_ctx(uint64_t num, char char_[1])
{
    struct ctx_t *__init_ctx = (struct ctx_t*)malloc(0x1000);
    if(__init_ctx==NULL){
        ERR("__init_ctx");
    }
    __init_ctx->ctx_num = (unsigned long)num;
    memset(__init_ctx->ctx_char,char_,0x100);
    __init_ctx->next = NULL;
    __init_ctx->prev = NULL;
    
    return __init_ctx;
}

int main(int argc, char const *argv[])
{
    struct ctx_t *ctx = alloc_ctx(10,"A");
    struct ctx_t *ctx_1 = (struct ctx_t*)malloc(0x200);
    ctx_1->ctx_num = 20;
    memset(ctx_1->ctx_char,"B",0x100); 
    ctx_1->next = (void*)system("/bin/sh");
    ctx_1->prev = 0x5aadb44d;

    return 0;
}
