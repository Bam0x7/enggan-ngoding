#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/mman.h>
#include<sys/stat.h>
#include<time.h>

#define FILE_NAME "file_mapping.txt"
const ssize_t file_size = 4096;

int open_file()
{
    int fd = open(FILE_NAME,O_RDWR|O_CREAT,(mode_t)0600);
    if(fd==-1){
        perror("open: ");
        return EXIT_FAILURE;
    }

    return fd;
}

void set_file_size(int fd)
{
    if(lseek(fd,file_size,SEEK_SET)==-1){
        close(fd);
        perror("lseek: ");
        exit(EXIT_FAILURE);
    }

    if(write(fd,"",1)==-1){
        close(fd);
        perror("write: ");
        exit(EXIT_FAILURE);
    }
}

void configure_file_options(int fd)
{
    int flags = fcntl(fd,F_GETFL);
    if(flags==-1){
        close(fd);
        perror("fcntl F_GETFL: ");
        exit(EXIT_FAILURE);
    }

    printf("file descriptor option before: %x\n" ,flags);

    flags |= O_NONBLOCK;

    if(fcntl(fd,F_SETFL,flags)==-1){
        close(fd);
        perror("fcntl F_SETFL: ");
        exit(EXIT_FAILURE);
    }

    printf("file descriptor option after: %x\n" ,flags);

}

void *map_file(int fd)
{
    void *mapped_data = mmap(NULL,file_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    if(mapped_data==MAP_FAILED){
        close(fd);
        perror("mmap: ");
        exit(EXIT_FAILURE);
    }

    return mapped_data;
}

void write_to_mapped_file(void *mapped_data,const char *pesan)
{
    sprintf(mapped_data,"%s",pesan);
}

void read_from_mapped_file(void *mapped_data)
{
    printf("konten file yang di petakan:\n%s\n",(char*)mapped_data);
}

void unmap_file(void *mapped_data)
{
    if(munmap(mapped_data,file_size)==-1){
        perror("munmap: ");
        exit(EXIT_FAILURE);
    }
}

void close_file(int fd)
{
    close(fd);
}

int main()
{
    int fd = open_file();

    set_file_size(fd);

    configure_file_options(fd);

    void *mapped_data = map_file(fd);

    printf("menulis dan memetakan memori\n");
    sleep(1);
    const char *pesan = "hallo, pemetaan memori pada file";
    write_to_mapped_file(mapped_data, pesan);
    puts("berhasil di tulis");
    puts("membaca file yang di petakan");
    sleep(1);

    read_from_mapped_file(mapped_data);

    unmap_file(mapped_data);
    close(fd);


    return EXIT_SUCCESS;
}
