#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

struct Node{
    int num;
    struct Node *next;
    struct Node *prev;
};
struct Node *head=NULL;
struct Node *tail=NULL;

struct Node *addNode(int num)
{
    struct Node *tmp = (struct Node*)malloc(sizeof(struct Node));
    if(tmp==NULL){
        perror("tmp malloc");
        exit(EXIT_FAILURE);
    }

    tmp->num = num;
    tmp->next = NULL;
    tmp->prev = NULL;

    return tmp;
}

void pushHead(int num)
{
    struct Node *temp = addNode(num);
    if(head==NULL){
        head=tail=temp;
    }else{
        head->next = temp;
        temp->prev = head;
        head = temp;   
    }
    
}

void pushTail(int num)
{
    struct Node *temp = addNode(num);
    if(head==NULL){
        head=tail=temp;
    }else{
        tail->prev = temp;
        temp->next = tail;
        tail = temp;
    }
}

void popHead()
{
    struct Node *temp;
    if(head==NULL){
        puts("data masih kosong");
        exit(EXIT_FAILURE);
    }

    if(head==tail){
        temp = head;
        head = tail = NULL;
        free(temp);
    }else{
        temp = head;
        head = head->prev;
        head->next = NULL;
        free(temp);
    }

}

void popTail()
{
    struct Node *temp;
    if(head==NULL){
        puts("data masih kosong");
        exit(EXIT_FAILURE);
    }
    if(head==tail){
        temp = head;
        head = tail = NULL;
        free(temp);
    }else{
        temp = tail;
        tail = tail->next;
        tail->prev = NULL;
        free(temp);
    }

}

void print_listAll()
{
    struct Node *curr = head;
    while(curr!=NULL){
        printf("%d -> " ,curr->num);
        curr = curr->prev;
    }
}

int main()
{
    pushHead(10);
    pushHead(20);
    pushTail(-20);
    pushTail(-10);
    popHead();
    popTail();
    print_listAll();
    printf("\n");

    return EXIT_SUCCESS;
}