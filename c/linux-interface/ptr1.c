#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc, char const *argv[])
{
    int val = 10;
    int *i_ptr = NULL;
    i_ptr = &val;

    char *c_ptr = NULL;
    c_ptr = (char*)&val;

    i_ptr++;
    c_ptr++;

    printf("%d = 0x%llx\n" ,i_ptr,*(unsigned long long*)&i_ptr);
    printf("%d = 0x%llx\n" ,c_ptr,*(unsigned long long*)&c_ptr);
    return 0;
}
