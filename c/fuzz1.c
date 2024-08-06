#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

struct mystruct{
    int my_int;
};

int main()
{
    struct mystruct *My = (struct mystruct*)malloc(0x10);
    My->my_int = 10;
    printf("mystruct: 0x%llx\n" ,*(unsigned long*)&My);

    return 0;
}