#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

struct person{
    char name[50];
    int age;
};

struct person *__init_person(char name[50], int age)
{
    struct person *self = malloc(sizeof(struct person));
    if(self==NULL){
        perror("self: ");   
    }

    strncpy(self->name,name,strlen(name));
    self->age = age;

    return self;
}

void print_all_data(struct person *self)
{
    printf("name: %s\n" ,self->name);
    printf("age: %d\n" ,self->age);
}

int main()
{
    struct person *self1,*self2;
    self1 = __init_person("Muhamad ibnu ruslan",24);
    self2 = self1;
    print_all_data(self1);
    print_all_data(self2);

    free(self2);
    free(self1);

    return EXIT_SUCCESS;
}

