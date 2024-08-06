#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdint.h>

unsigned long *page_1;
int main()
{
    uint64_t addr = 0xdeadbeef;
    uint64_t offset_hight = ((addr >> 32) & 0xFFFFFFFF);
    uint64_t offset_low = (addr >> 0xFFFFFFFF);

    printf("hight: 0x%lx\n" ,offset_hight);
    printf("low: 0x%lx\n" ,offset_low);

    ((unsigned long *)(page_1))[0xff0/8] = 1;
    printf("nilai: %ln\n" ,page_1);
}