#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<keyutils.h>
#include<sched.h>
#include<stdint.h>
#include<sys/types.h>
#include<sys/syscall.h>
#define KEY_NAME "kunci_saya"
int main()
{
    key_serial_t key = keyctl(KEYCTL_JOIN_SESSION_KEYRING,KEY_NAME);
    if(key==-1){
        perror("keyctl");
        return EXIT_FAILURE;
    }

    printf("nomor kunci yang di buat: %d\n" ,key);

    key_serial_t new_key = keyctl_get_keyring_ID(key,0x10);
    if(new_key==-1){
        perror("keyctl_get_keyring_ID");
        return EXIT_FAILURE;
    }
    printf("key baru: %d\n" ,new_key);

    pid_t pid = getpid();
    printf("pid before: %d\n" ,pid);
    cpu_set_t cpu_set;
    CPU_ZERO(&cpu_set);
    CPU_SET(0,&cpu_set);

    if(sched_getaffinity(pid,sizeof(cpu_set),&cpu_set)==-1){
        perror("sched_getaffinity");
        return EXIT_FAILURE;
    }
    printf("cpu berhasil di set ke 0\n");
    printf("pid after cpu(0): %d,%llx\n" ,pid,*(unsigned long long*)&cpu_set);
    return EXIT_SUCCESS;
}
