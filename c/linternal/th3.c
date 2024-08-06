#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/stat.h>

int num = 0;
void *func_thread()
{
	num+=1;
	printf("num: %d\n", num);

	return NULL;
}	

int main()
{
	pthread_t th[10];
	for(int i = 0; i < 10; i++){
		if(pthread_create(&th[i],NULL,func_thread,NULL)==-1){
			perror("pthread_create:");
			return EXIT_FAILURE;
		}
	}

	for(int i = 0; i < 10; i++){
		if(pthread_join(th[i],NULL)==-1){
			perror("pthread_join");
			return EXIT_FAILURE;
		}
	}

	return EXIT_FAILURE;

}	
