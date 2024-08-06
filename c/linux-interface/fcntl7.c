#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

int setFlags(int fd, int flags);
int removeFlags(int fd, int flags);
void strFlagReturn(int returnValue);
void printFlags(int fd);


int main(void){
    
    int fdOne = open("another.txt", O_CREAT | O_TRUNC | O_RDWR, (mode_t)0664);
    
    if(fdOne < 0){
        printf("Error creating file descriptor.\n");
        exit(EXIT_FAILURE);
    }
    
    printFlags(fdOne);
    strFlagReturn(setFlags(fdOne, O_APPEND));
    printFlags(fdOne);
    strFlagReturn(setFlags(fdOne, O_NONBLOCK));
    printFlags(fdOne);
    strFlagReturn(removeFlags(fdOne, O_NONBLOCK));
    printFlags(fdOne);
    
    return 0;
    
}


void strFlagReturn(int returnVal){
    switch(returnVal){
        case 0:
            printf("Flags value altered successfully.\n");
            break;
        case -1:
            printf("Could not get flags to alter them.\n");
            break;
        case -2:
            printf("Could not alter flags after retrieving them.\n");
            break;
    }
    
}
void printFlags(int fd){
    int flags;
    
    if((flags=fcntl(fd, F_GETFL, 0))<0){
        printf("Couldn't access flags for fd %d.\n", fd);
        return;
    } else {
        printf("File Desc. %d: ", fd);
    }
    switch(flags & O_ACCMODE){
        case O_RDONLY:
            printf("Read only. ");
            break;
        case O_WRONLY:
            printf("Write only. ");
            break;
        case O_RDWR:
            printf("Read and write. ");
            break;
    } // end switch-----
    
    if(flags & O_APPEND){
        printf(" Append. ");
    }
    
    if(flags & O_NONBLOCK){
        printf(" Non-blocking.");
    }
    
    printf("\n");
}

//this uses logical and to remove flags
int removeFlags(int fd, int flags){
    int oldFlags;
    
    if((oldFlags = fcntl(fd, F_GETFL, 0))<0){
        return -1;
    }
   
    //AND the flag values
    //and inverse the flags parameter
    flags = ~flags & oldFlags;
    
    if(fcntl(fd, F_SETFL, flags) < 0){
        return -2;
    }
    
    return 0;
    
}

//this uses logical or to add flags
int setFlags(int fd, int flags){
    int oldFlags;
    
    if((oldFlags = fcntl(fd, F_GETFL, 0))<0){
        return -1;
    }
    
    //OR the flags values
    flags = flags | oldFlags;

    if((fcntl(fd, F_SETFL, flags))<0){
        return -2;
    } 
    
    return 0;
}