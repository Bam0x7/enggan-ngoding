#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
#include<errno.h>

int main()
{
    int fd_1,fd_2,fd_3;

    fd_1 = open("misc.txt",O_CREAT|O_TRUNC,(mode_t)0644);
    if(fd_1==-1){
        perror("open: fd1 ");
        if(errno==EACCES){
            printf("error %d: EACCES: permission denied\n" ,EACCES);
        }
        return EXIT_FAILURE;
    }else{
        printf("file di buka\n");
        printf("dengan file deskriptor %d\n" ,fd_1);
    }

    if((fd_2 = fcntl(fd_1,F_DUPFD,5))==-1){
        perror("fd_2 fcntl");
        return EXIT_FAILURE;
    }else{
        printf("fd_1 berhasil di duplikat\n");
        printf("fd_2: %d\n" ,fd_2);
    }

    if((fd_3 = fcntl(fd_1,F_DUPFD,11))==-1){
        perror("fd_3 fcntl");
        return EXIT_FAILURE;
    }else{
        printf("fd1 berhasil di duplikat\n");
        printf("fd_3: %d\n" ,fd_3);
    }

    close(fd_1);
    close(fd_2);
    close(fd_3);

    return EXIT_SUCCESS;

}