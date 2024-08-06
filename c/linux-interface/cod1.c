#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>

#define ERR(msg)do{\
        printf("%s\n"); \
    }while(0)

struct Person{
    char name[250];
    char skill[250];
    int age;
};

struct Employee{
    struct Person per;
    char position[250];
    int experience;
    struct emp *next,*prev;
};

struct Employee *head=NULL;
struct Employee *tail=NULL;

struct Employee *__init_(char *nm, char *sk, char *pos, int exp, int ag)
{
    struct Employee *emp = (struct Employee*)malloc(sizeof(struct Employee));
    if(emp==NULL){
        ERR("emp gagal di alokasikan");
    }

    strncpy(emp->per.name,nm,strlen(nm));
    strncpy(emp->per.skill,sk,strlen(sk));
    strncpy(emp->position,pos,strlen(pos));
    emp->experience = exp;
    emp->per.age = ag;
    emp->next = NULL;
    emp->prev = NULL;

    return emp;
}

void addEmp_head(char *nm, char *sk, char *pos, int exp, int ag)
{
    struct Employee *temp = __init_(nm,sk,pos,exp,ag);
    if(temp==NULL){
        ERR("addEmp_head allocation error");
    }
    if(head==NULL){
        head = tail = temp;
    }else{
        head->next = temp;
        temp->prev = head;
        head = temp;
    }
}

void addEmp_tail(char *nm, char *sk, char *pos, int exp, int ag)
{
    struct Employee *temp = __init_(nm,sk,pos,exp,ag);
    if(temp==NULL){
        ERR("addEmp_tail allocation error");
    }
    if(tail==NULL){
        head= tail = temp;
    }else{
        tail->prev = temp;
        temp->next = tail;
        tail = temp;
    }
}


void popEmpHead()
{
    struct Employee *temp;
    if(head==NULL){
        ERR("data masih kosong");
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
        puts("-------------------");
        puts("-->data di hapus<--");
        puts("-------------------");
    }
}

void popEmpTail()
{
    struct Employee *temp;
    if(tail==NULL){
        ERR("data masih kosong");
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
        puts("-------------------");
        puts("-->data di hapus<--");
        puts("-------------------");
    }
    
}

void PrintData()
{
    struct Employee *curr = head;
    if(curr==NULL){
        ERR("data masih kosong");
        exit(EXIT_FAILURE);
    }
    while(curr!=NULL){
        printf("Name: %s\n" ,curr->per.name);
        printf("Age: %d\n" ,curr->per.age);
        if(curr->per.age >= 25){
            puts("status: promotion");
        }
        printf("Skill: %s\n" ,curr->per.skill);
        printf("Job: %s\n" ,curr->position);
        printf("Experience: %d years\n" ,curr->experience);
        printf("==========================\n");
        curr = curr->prev;
    }
}

void checkage()
{
    struct Employee *temp = head;
    while(temp!=NULL){
        if(temp->per.age > head->per.age){
            printf("Pegawai yang paling tua adalah: %s dengan usia %d\n" ,temp->per.name,temp->per.age);
        }
        temp = temp->prev;
    }
}

int main()
{
    addEmp_head("Ibnu Ruslan", "C++","Game Programmer", 4, 27);
    addEmp_tail("Bam Mazino","Vulnerabillity Research", "Red Teaming", 5, 25);

    PrintData();
    checkage();
    popEmpTail();
    addEmp_tail("Pekkaz","Python","Data Science",6,23);
    PrintData();

    return EXIT_SUCCESS;    
}