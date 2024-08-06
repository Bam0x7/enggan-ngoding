#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <sched.h>
#include <pthread.h>
#include <keyutils.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/xattr.h>

void *thread_func(void *arg)
{
    key_serial_t my_key = *(key_serial_t*)arg;
    key_serial_t retrieve_key = keyctl(KEYCTL_GET_KEYRING_ID,my_key);
    
    if(retrieve_key==-1){
        perror("keyctl");
        exit(EXIT_FAILURE);
    }

    printf("kunci yang baru di dapatkan: %d\n" ,retrieve_key);

    return NULL;
}

int main(int argc, char const *argv[])
{
    key_serial_t key = keyctl(KEYCTL_JOIN_SESSION_KEYRING, "kunci_saya");
    if(key==-1){
        perror("keyctl");
        return EXIT_FAILURE;
    }

    printf("kunci berhasil di buat, kunci: %d\n" ,key);
    pthread_t thread;
    if(pthread_create(&thread,NULL,thread_func,(void *)key)==-1){
        perror("pthread_create()");
        return EXIT_FAILURE;
    }

    //menetapkan thread ke cpu dengan ID 0

    cpu_set_t cpu_set;
    CPU_ZERO(&cpu_set);
    CPU_SET(0,&cpu_set);

    pid_t pid = fork();
    if(pid==-1){
        perror("fork");
        return EXIT_FAILURE;
    }
    
    if(sched_setaffinity(pid,sizeof(cpu_set),&cpu_set)==-1){
        perror("pthread_setaffinity_np");
        return EXIT_FAILURE;
    }

    if(pthread_join(thread,NULL)==-1){
        perror("pthread_join");
        return EXIT_FAILURE;
    }

    if(keyctl(KEYCTL_REVOKE,key)==-1){
        perror("keyctl_revoke");
        return EXIT_FAILURE;
    }

    printf("kunci di revoke\n");
    return 0;
}

