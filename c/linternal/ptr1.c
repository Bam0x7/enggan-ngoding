#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
    int num = 10;
    int *ptr = &num;

    *ptr = 20;

    printf("%d\n" ,num);
    printf("%d\n" ,*ptr);

    printf("%016lx\n" ,(unsigned long)&num);
    printf("%016lx\n" ,(unsigned long)ptr);

    return 0;
}