#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void){
    
    printf("duplicate an existing file descriptor (F_DUPFD) %d\n", F_DUPFD);
    printf("get file descriptor flags (F_GETFD) %d\n", F_GETFD);
    printf("set file descriptor flags (F_SETFD) %d\n", F_SETFD);
    printf("get file status flags (F_GETFL) %d\n", F_GETFL);
    printf("set file status flags (F_SETFL) %d\n", F_SETFL);
    printf("get record locks (F_GETLK) %d\n", F_GETLK);
    printf("set record locks (F_SETLK) %d\n", F_SETLK);
    
    return 0;
    
}