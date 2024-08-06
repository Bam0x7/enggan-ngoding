#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

struct number{
    int num;
    struct number *next;
    struct number *prev;
};

struct number *__init__number(int num)
{
    struct number *num_ = (struct number*)malloc(sizeof(struct number));
    if(num_==-1){
        perror("malloc");
        return EXIT_FAILURE;
    }

    num_->num = num;
    num_->next = NULL;
    num_->prev = NULL;

    return num_;
}

int *add_num(struct number *root,int val)
{
    if(root==NULL){
        return __init__number(val);
    }

    if(val < root->num){
        root->prev = add_num(root->prev,val);
    }else if(val > root->num){
        root->next = add_num(root->next,val);
    }

    return root;
}

void inorder(struct number *root)
{
    if(root!=NULL){
        inorder(root->prev);
        printf("%d " ,root->num);
        inorder(root->next);
    }
}

void postorder(struct number *root)
{
    if(root!=NULL){
        printf("%d " ,root->num);
        postorder(root->prev);
        postorder(root->next);
    }
}

void preorder(struct number *root)
{
    if(root!=NULL){
        preorder(root->prev);
        preorder(root->next);
        printf("%d " ,root->num);
    }
}

int main()
{
    struct number *root = NULL;
    root = add_num(root,50);
    add_num(root,30);
    add_num(root,40);
    add_num(root,50);
    add_num(root,60);
    add_num(root,70);
    add_num(root,10);
    add_num(root,80);

    printf("inorder\n");
    inorder(root);
    printf("\n");

    printf("postorder\n");
    postorder(root);
    printf("\n");

    printf("preorder\n");
    preorder(root);
    printf("\n");

    return EXIT_SUCCESS;
}