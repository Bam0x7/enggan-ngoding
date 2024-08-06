#include<stdio.h>
#include<stdlib.h>

struct number{
    int x;
    int y;
};

int main()
{
    int num=0,*ptr_num=NULL;
    struct number *Number = NULL;

    Number = malloc(sizeof(struct number));

    for(int i=0;i<10;i++){
        Number[i].x = i;
        Number[i].y = i + 5;

        printf("%d" ,*(Number+i));
        printf("\n");
        printf("%d\n" ,(*(Number+i)).y);
    }

    return 0;
}