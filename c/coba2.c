#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

struct person{
    char name[30];
    int age;
    struct person *fd;
};

struct person *__init_person(char name[30], int age)
{
    
}    

