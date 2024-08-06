#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
#include<mosquitto.h>
#include<sensors/sensors.h>

int shared_variable;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t sem;
void *func_thread_1()
{
    if(sem_wait(&sem)==-1){
        perror("pthread_mutex_lock()");
        exit(EXIT_FAILURE);
    }
    for(int i=0;i<10000;i++){      
        shared_variable++;
        printf("func_thread_1() %d\n",i);
    }
    if(sem_post(&sem)==-1){
        perror("pthread_mutex_unlock()");
        exit(EXIT_FAILURE);
    }
    return NULL;
}
void *func_thread_2()
{
    for(int i=0;i<10000;i++){
        shared_variable++;
        printf("func_thread_2() %d\n",i);
    }
    return NULL;
}
int main(int argc, char const *argv[])
{
    pthread_t thr1,thr2;
    sem_init(&sem,0,1);

    if(pthread_create(&thr1,NULL,func_thread_1,NULL)==-1){
        perror("pthread_create() thr1");
        return EXIT_FAILURE;
    }
    if(pthread_create(&thr2,NULL,func_thread_2,NULL)==-1){
        perror("pthread_create() thr2");
        return EXIT_FAILURE;
    }

    if(pthread_join(thr1,NULL)==-1){
        perror("pthread_join() thr1");
        return EXIT_FAILURE;
    }
    if(pthread_join(thr2,NULL)==-1){
        perror("pthread_join() thr2");
        return EXIT_FAILURE;
    }
    pthread_mutex_destroy(&mutex);
    sem_destroy(&sem);
    printf("nilai shared_variable: %d\n" ,shared_variable);
    return 0;
}
