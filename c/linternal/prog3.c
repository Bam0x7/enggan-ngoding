#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>


int main()
{
	char name[24], ucopy[50] = "ibnu ruslan";
	memcpy(name,ucopy,strlen(ucopy));

	int len= strlen(name);

	printf("name: %s\n" ,name);
	printf("len of name: %d\n" ,len);


	return 0;

}
	
