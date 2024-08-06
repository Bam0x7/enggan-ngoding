#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/mman.h>

#define BUFF 50

struct class{
    char cls_name[BUFF];
    int val;
};
struct person{
    char name[BUFF];
    int age;
    struct class cls;
    struct person *next;
    struct person *prev;
};

struct person *self=NULL;

struct person *create_person(char name[BUFF],char cls_name[BUFF],int age, int val)
{
    struct person *self = (struct person *)malloc(sizeof(struct person));
    if(self==NULL){
        perror("malloc_self");
        return EXIT_FAILURE;
    }

    strncpy(self->name,name,strlen(name));
    strncpy(self->cls.cls_name,cls_name,strlen(cls_name));
    self->age = age;
    self->cls.val = val;
    self->next = NULL;
    self->prev = NULL;

    return self;    
}

void add_list_person(char name[BUFF],char cls_name[BUFF],int age, int val)
{
    struct person *tmp = create_person(name,cls_name,age,val);

    if(self==NULL){
        self = tmp;
    }else{
        self->next = tmp;
        tmp->prev = self;
        self = tmp;
    }
    
}

void delete_list()
{
    struct person *curr;
    if(self==NULL){
        puts("data kosong");

    }else{
        curr = self;
        self = self->prev;
        curr->next = NULL;
        curr->prev = NULL;
        free(curr);
        printf("data di hapus\n");
    }
}

void print_list()
{
    struct person *curr = self->prev;
    while(curr!=NULL){
        printf("name: %s\n" ,curr->name);
        printf("class: %s\n" ,curr->cls.cls_name);
        printf("age: %d\n" ,curr->age);
        printf("val: %d\n" ,curr->cls.val);
        curr = curr->next;
    }
}

int main()
{
    add_list_person("bam","xii_rpl_2",18,90);
    add_list_person("sangu","xii_rpl_1",18,70);
    print_list();
    delete_list();
  
    return EXIT_SUCCESS;
}