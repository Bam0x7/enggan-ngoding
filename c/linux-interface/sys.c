#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/syscall.h>
#include<string.h>

int main(int argc, char const *argv[])
{
    char *pesan = "hallo kernel\n";

    syscall(__NR_write,1,pesan,strlen(pesan));
    return 0;
}
