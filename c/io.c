#include <asm-generic/ioctls.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ioctl.h>

int main()
{
    struct winsize w;

    if(ioctl(STDOUT_FILENO,TIOCGWINSZ,&w)==-1){
        perror("ioctl: ");
        return EXIT_FAILURE;
    }

    printf("terminal high: %d\n" ,w.ws_row);
    printf("terminal width: %d\n" ,w.ws_col);

    return EXIT_SUCCESS;
}