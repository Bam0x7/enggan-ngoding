#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>


struct num_t{
    int num;
    struct num_t *next;
};

int main()
{
    struct num_t *Num = (struct num_t*)malloc(sizeof(struct num_t));
    if(Num==NULL){
        perror("Num malloc");
        return EXIT_FAILURE;
    }

    Num->num = 10;
    Num->next = (struct num_t*)malloc(sizeof(struct num_t));

    if(Num->next==NULL){
        perror("num->next malloc");
        free(Num);
        return EXIT_FAILURE;
    }

    Num->next->num = 20;
    Num->next->next = NULL;

    for(struct num_t *curr = Num;curr!=NULL;curr = curr->next){
        printf("%d\n" ,curr->num);
    }

    free(Num->next);
    free(Num);
    Num = Num->next = NULL;
}
