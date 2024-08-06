#include<stdio.h>
#include<stdlib.h>

struct Node{
    int val;
    struct Node *next;
};

int main()
{
    struct Node *number = (struct Node*)malloc(sizeof(struct Node));
    if(number==NULL){
        perror("number");
    }
    
    number->val = 10;
    number->next = malloc(sizeof(number));
    number->next->val = 20;
    number->next->next = malloc(sizeof(number));
    number->next->next->val = 30;
    number->next->next->next = malloc(sizeof(number));
    number->next->next->next->val = 40;
    number->next->next->next->next = NULL;
    while(number!=NULL){
        printf("%d\n" ,number->val);
        number = number->next;
    }

    return EXIT_SUCCESS;
}