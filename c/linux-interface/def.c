#include<stdio.h>
#define PRINT(a) printf("%d\n" ,a);
#define LOOP(i,n,j) for(i=n;i<j;i++){
#define END }

#define msg_error(msg) \
        do{perror(msg); \
        exit(EXIT_FAILURE); \
        }while(0)

int main(int argc, char const *argv[])
{
    int counter = 0;
    LOOP(counter,1,10)
        PRINT(counter)
    END        
    return 0;
}
