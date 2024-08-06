#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

int return_value(const char * my_str, int num)
{
    char *end;
    long int num_2 = strtol(my_str,&end,num);
    if(num_2==-1){
        return EXIT_FAILURE;
    }

    return num_2;
}

int main()
{
    int result = 0xfff88880007cdd70 & 0xfff;
    printf("0x%016lx\n" ,*(unsigned long*)&result);

    char *my_str = "1234abcd";
    char *end;
    long int num = strtol(my_str,&end,0x10);

    printf("%016lx\n" ,num);
    printf("%s\n" ,end);

    long int second_num = return_value("deadbeef",0x9);
    printf("%016lx\n" ,second_num);

    char *buff[0x1000];
    unsigned long ptr = 0xdeadbeef;
    memset(buff,0,sizeof(buff));
    memcpy((void *)&buff,(void *)&ptr,sizeof(ptr));
    printf("0x%016lx\n" ,*(unsigned long*)&buff);

    return 0;

}
