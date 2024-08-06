#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<liburing.h>

int main(int argc, char const *argv[])
{
    int a,b,c;
    a = 10;
    b = 12;
    c = a ^ b;
    int d = a | b;
    int e = a & b;
    printf("c: %d, d: %d, e: %d\n" ,c,d,e);
    int j = 20;
    printf("%x\n" ,&j);
    printf("%llx\n" ,(unsigned long long)&j);
    int ptr = (unsigned long)&j;
    printf("%x\n" ,&ptr);
    printf("%llx\n" ,(unsigned long long)&ptr-0x18);
    int pptr = *(unsigned long *)&ptr;
    printf("%llx\n" ,(unsigned long long)&pptr+0x10);
    printf("%lld\n" ,ptr);
    printf("%lld\n" ,pptr);

    return 0;
}
