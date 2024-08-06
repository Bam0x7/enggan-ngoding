#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

void sort(int arr[], int n);

int main()
{
    int arr[5],n=5;

    for(int i=0;i<n;i++){
        printf("> ");
        scanf("%d" ,&arr[i]);
    }

    sort(arr,n);

    return EXIT_SUCCESS;
}

void sort(int arr[],int n)
{
    int i,j,*tmp;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(arr[j] > arr[i]){
                tmp = arr[j];
                arr[j] = arr[i];
                arr[i] = tmp;
            }
        }
    }

    for(i=0;i<n;i++){
        printf("%d = arr[%d]\n" ,i,arr[i]);
    }
}