#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int add(int a, int b){
    return a + b;
}
int sum(int a, int b)
{
    return add(a,b);
}

int main(int argc, char const *argv[])
{
    int (*func)(int,int);
    func = NULL;
    func = &sum;
    int result = func(10,10);
    printf("hasil: %d, offset: 0x%llx\n",result,(unsigned long long*)&result);
    return 0;
}
