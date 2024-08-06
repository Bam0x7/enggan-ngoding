#include<stdio.h>
#include <sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/mman.h>
#include<sys/stat.h>

#define FILE_NAME "example.txt"
int main()
{
    int fd = open(FILE_NAME,O_CREAT|O_RDWR|O_RDONLY,(mode_t)0600);
    if(fd==-1){
        perror("open: ");
        return EXIT_FAILURE;
    }

    const ssize_t file_size = 4096;
    if(lseek(fd,file_size,SEEK_SET)==-1){
        close(fd);
        perror("lseek: ");
        return EXIT_FAILURE;
    }

    if(write(fd,"",1)==-1){
        close(fd);
        perror("write: ");
        return EXIT_FAILURE;
    }

    char *mapped_data = mmap(NULL,file_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    if(mapped_data == MAP_FAILED){
        close(fd);
        perror("mmap: ");
        return EXIT_FAILURE;

    }

    const char *pesan = "hallo, pemetaan memory menggunakan mmap()";

    sprintf(mapped_data,"%s",pesan);
    if(munmap(mapped_data,file_size)==-1){
        close(fd);
        perror("munmap: ");
        return EXIT_FAILURE;
    }

    close(fd);
    return EXIT_SUCCESS;
}