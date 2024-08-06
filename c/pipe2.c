#define _GNU_SOURCE
#include<stdlib.h>
#include<stdio.h>
#include<sched.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/stat.h>
#include<sys/types.h>

int main(int argc, char const *argv[])
{
    cpu_set_t cpu;
    CPU_ZERO(&cpu);
    int target_cpu = 0;
    CPU_SET(target_cpu,&cpu);

    pid_t pid = getpid();

    if(pid==-1){
        perror("getpid()");
        return EXIT_FAILURE;
    }

    if(sched_setaffinity(pid,sizeof(cpu_set_t),&cpu)==-1){
        perror("sched_setaffinity");
        return EXIT_FAILURE;
    }

    for(int i=0;i<10000000;i++){
        i+=1;
    }

    printf("proses: %d sudah di set dengan affinitas cpu: %d\n" ,pid,target_cpu);
    return 0;
}
