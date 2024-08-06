#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

struct Node{
    int val;
    struct Node *next;
};

struct Node *head = NULL;

struct Node *creat(int val)
{
    struct Node *temp = (struct Node*)malloc(sizeof(struct Node));
    if(temp==NULL){
        perror("creat: temp");
        exit(EXIT_FAILURE);
    }
    temp->val = val;
    temp->next = NULL;

    return temp;
}
