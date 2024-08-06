#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/mman.h>

#define BUFF 50

void main_menu();

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
    main_menu();
}

void print_list()
{
    struct person *curr = self->prev;
    if(self==NULL){
        perror("data masih kosong\n");
        exit(EXIT_FAILURE);
    }
    while(curr!=NULL){
        printf("name: %s\n" ,curr->name);
        printf("class: %s\n" ,curr->cls.cls_name);
        printf("age: %d\n" ,curr->age);
        printf("val: %d\n" ,curr->cls.val);
        curr = curr->next;
    }
    main_menu();
}


void input_data()
{
input:    
    char name[BUFF],cls_name[BUFF];
    int age,val;

    printf("Name: ");
    scanf("%s",name);

    printf("class name: ");
    scanf("%s",cls_name);

    printf("age: ");
    scanf("%d",&age);

    printf("value: ");
    scanf("%d",&val);
    add_list_person(name,cls_name,age,val);
    char opt[4];
    while(1){
        printf("lagi? (yes/no) >> ");
        scanf("%s",opt);

        if(strcmp(opt,"yes")==0){          
            goto input;
        }else if(strcmp(opt,"no")==0){
            goto main_;
        }else{
            puts("opsi tidak tersedia");
            goto exitFailure;
        }
    }
main_:
    main_menu();    
exitFailure:
    exit(EXIT_FAILURE);    
}

void main_menu()
{
menu:    
    int opt;

    printf("menu\n");
    printf("1. input data\n");
    printf("2. tampil data\n");
    printf("3. tampil data\n");
    printf("4. exit\n");
    printf(">> ");
    scanf("%d" ,&opt);

    if(opt==1){
        input_data();
    }else if(opt==2){
        print_list();
    }else if(opt==3){
        delete_list();
    }else if(opt==4){
        goto exitMenu;
    }else{
        printf("opsi tidak tersedia\n");
        goto menu;
    }
exitMenu:
    printf("anda keluar\n");
    exit(EXIT_FAILURE);
}

int main()
{
    main_menu();
         
    return EXIT_SUCCESS;
}