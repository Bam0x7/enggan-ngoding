#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

struct person{
	char person_name[50];
	int person_age;
};

int main()
{
	struct person *self = malloc(sizeof(struct person));
	if(self==NULL){
		perror("person/self ");
	}
	printf("bangsat\n");
	if(10 < 20){
		printf("lebih kecil\n");
	}else{
		puts("lebih besar");
	}
	return 0;
}
