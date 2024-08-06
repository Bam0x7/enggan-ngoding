#include<stdio.h>
#include<stdlib.h>

struct list{
    int num;
    struct list *fd;
};

struct list *head=NULL;

struct list *addNode(int val)
{
    struct list *Node = (struct list *)malloc(sizeof(struct list));
    if(Node==NULL){
        perror("Node");
        exit(EXIT_FAILURE);
    }

    Node->num = val;
    Node->fd = NULL;

    return Node;
}

void addNumBeg(int val)
{
    struct list *tmp = addNode(val);
    tmp->fd = head;
    head = tmp;
}

void DelNum()
{
    struct list *tmp = head;
    if(head==NULL){
        head = NULL;
    }else{
        head = tmp->fd;
        free(tmp);
    }
}

int main()
{    
    addNumBeg(10);
    addNumBeg(20);
    addNumBeg(30);
    addNumBeg(40);
    addNumBeg(50);
    
    DelNum();

    struct list *tmp = head;

    int num = 30;
    while(tmp!=NULL){
        printf("%d\n" ,tmp->num);
        if(num==tmp->num){
            printf("nomor di temukan\n");
        }else{
            printf("nomor tersebut tidak ada\n");
        }
        tmp = tmp->fd;
    }

    return EXIT_SUCCESS;
}