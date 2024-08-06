#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/stat.h>

void *funcThread()
{
	int num = 100;
	for(int i=0; i < num; i++){
		printf("num: %d\n" ,i+=num);
	}	
}	
int main()
{
	pthread_t th;
	int x = 10;
	if(pthread_create(&th,NULL,funcThread,NULL)==-1){
		perror("pthread_create");
		return EXIT_FAILURE;
	
	}	

	if(pthread_join(th,NULL)==-1){
		perror("pthread_join");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}	
