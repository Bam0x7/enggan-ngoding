#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<sys/mman.h>
#include<sys/stat.h>
#include<sys/xattr.h>

const char *file_path = "file_fcntl.txt";
const char *attr_value = "file_saya";
const char *attr_name = "file.custom_fcntl";
const size_t file_size = 4090;


int open_file()
{
    int fd = open(file_path,O_RDWR|O_CREAT,(mode_t)0666);
    if(fd==-1){
        perror("open");
        return EXIT_FAILURE;
    }

    return fd;
}

void set_file_size(int fd)
{
    if(lseek(fd,file_size-1,SEEK_SET)==-1){
        close(fd);
        perror("lseek");
        exit(EXIT_FAILURE);
    }
    if(write(fd,"",1)==-1){
        close(fd);
        exit(EXIT_FAILURE);
    }
}

void file_option(int fd)
{
    int flag = fcntl(fd,F_GETFL);
    if(flag==-1){
        close(fd);
        perror("fcntl F_GETFL");
        exit(EXIT_FAILURE);
    }
    printf("file descriptor before: %x\n" ,flag);

    //menambahkan opsi non-blocking
    flag |= O_NONBLOCK;

    if(fcntl(fd,F_SETFL)==-1){
        close(fd);
        perror("fcntl F_SETFL");
        exit(EXIT_FAILURE);
    }
    printf("file descriptor after: %x\n" ,flag);
}

void *map_file(int fd)
{
    void *mapped_file = mmap(NULL,file_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    if(mapped_file == MAP_FAILED){
        close(fd);
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    return mapped_file;
}

void write_file(void *mapped_file, const char *msg)
{
    sprintf(mapped_file, "%s", msg);
}

void read_file(void *mapped_file)
{
    printf("file yang di mapping: %s\n" ,(char *)mapped_file);
}

void unmap_file(void *mapped_file, size_t file_size)
{
    if(munmap(mapped_file,file_size)==-1){
        perror("munmap");
        exit(EXIT_FAILURE);
    }
}

void close_file(int fd)
{
    close(fd);
}

void set_attr()
{
    int result = setxattr(file_path,attr_name,attr_value,strlen(attr_value),0);
    if(result==-1){
        perror("setxattr");
        exit(EXIT_FAILURE);
    }

}

int main()
{
    int fd = open_file();
    set_file_size(fd);
    file_option(fd);
    void *mapped_file = map_file(fd);
    const char *msg = "mapping file on memory";
    //set_attr();
    write_file(mapped_file,msg);
    read_file(mapped_file);
    unmap_file(mapped_file,file_size);
    close_file(fd);
}