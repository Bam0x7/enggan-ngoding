#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc, char const *argv[])
{
    printf("proses id saat ini: %d\n" ,getpid());
    printf("sebelum memanggil fork()\n");

    __pid_t ret = fork();
    if(ret){
        printf("proses anak di panggil dengan PID: %d\n" ,ret);
    }else{
        printf("proses anak dengan PID: %d\n" ,getpid());
    }
    return 0;
}
