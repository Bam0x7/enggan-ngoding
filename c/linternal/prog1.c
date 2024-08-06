#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>

int main()
{
    int n=5,arr[0x5] = {1,2,3,4,5},i;
    for(i=0;i<n;i++){
        printf("%d = %d\n" ,i,arr[i]);
    }

    int *ptr = arr;
    *(ptr+1) = 3;
    *(ptr+3) = 6;
    *(ptr+0) = 9;

    for(i=0;i<n;i++){
        printf("%d = %d\n" ,i,arr[i]);
    }

    for(i=0;i<n;i++){
        printf("%d = 0x%016lx\n" ,i,(unsigned long)(arr + i));
    }
    printf("0x%016lx\n" ,(unsigned long)(ptr + 2));

    int temp;
    for(int i=0; i<n;i++){
        for(int j=0;j<n;j++){
            if(arr[j]>arr[i]){
                temp = arr[j];
                arr[j] = arr[i];
                arr[i] = temp;
            }
        }
    }

    for(i=0;i<n;i++){
        printf("%d = %d\n" ,i,arr[i]);
    }

    return 0;
}
