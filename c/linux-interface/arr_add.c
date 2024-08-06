#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>

int main()
{
    int arr[100],n,index,indexElement;

    printf("masukan jumlah element: ");
    scanf("%d",&n);

    printf("element array\n");
    for(int i=0;i<n;i++){
        printf("index %d: " ,i+1);
        scanf("%d",&arr[i]);
    }

    for(int i=0;i<n;i++){
        printf("index %d = %d\n" ,i+1,arr[i]);
    }

    printf("masukan element yang ingin di ganti: ");
    scanf("%d",&indexElement);

    printf("di index ke berapa ingin di ganti: ");
    scanf("%d",&index);

    if(index > n){
        printf("index melebihi jumlah index pada array\n");
        return EXIT_FAILURE;
    }

    arr[index-1] = indexElement;

    printf("element pada index %d di rubah\n" ,index);
    for(int i=0;i<n;i++){
        printf("index %d: %d\n" ,i+1,arr[i]);
    }
    return EXIT_SUCCESS;
}