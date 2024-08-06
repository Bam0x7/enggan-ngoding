#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

void readFlags(int fd){
    int returnValue;
    if((returnValue = fcntl(fd, F_GETFL, 0))<0){
        printf("Error opening file descriptor %d.\n", fd);
        return;
    }
    printf("Access mode flags for fd %d: ", fd);
    switch(returnValue & O_ACCMODE){
        case O_RDONLY:
            printf("Read only. ");
            break;
        case O_WRONLY:
            printf("Write only. ");
            break;
        case O_RDWR:
            printf("Read and write. ");
            break;
        default:
            printf("Unknown access mode. ");
            break;
    } // end switch
    if(returnValue & O_APPEND){
        printf("+Append.");
    }
    if(returnValue & O_NONBLOCK){
        printf("+Nonblocking");
    }
    printf("\n");
} // end function readFlags ---------------

int main(void){
    
    int fdOne, fdTwo;
    
    if((fdOne = open("append.txt", O_CREAT | O_APPEND, (mode_t)0664))<0){
        printf("Error opening append.txt.\n");
        exit(EXIT_FAILURE);
    } else {
        printf("File opened with fd %d.\n", fdOne);
    }
    
    
    if((fdTwo = open("nonblocking.txt", O_CREAT | O_NONBLOCK, (mode_t)0664))<0){
       printf("Error opening nonblocking.txt");
       exit(EXIT_FAILURE);
    } else {
        printf("File opened with fd %d.\n", fdTwo);
    }
    
    readFlags(fdOne);
    readFlags(fdTwo);
    
    if((close(fdOne))<0){
        printf("Error closing fdOne.\n");
        exit(EXIT_FAILURE);
    }
    
    if((close(fdTwo))<0){
        printf("Error closing fdTwo.\n");
        exit(EXIT_FAILURE);
    }
    
    return 0;
    
}